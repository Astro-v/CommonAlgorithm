#include <boost/signals2.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

struct StatQuery;
struct Game;

class Creature;
class Goblin;
class GoblinKing;

class CreatureModifier;
class AddDefenceModifier;
class AddAttackModifier;

struct Game
{
    boost::signals2::signal<void(StatQuery&, Creature&)> queries;
    std::vector<Creature*> creatures;
};

struct StatQuery
{
    enum Statistic
    {
        attack,
        defense
    } statistic;
    int result;

    StatQuery(Statistic statistic, int result) : statistic(statistic), result(result)
    {
    }
};

class CreatureModifier
{
    Game& game;
    Creature& creature;

   public:
    virtual ~CreatureModifier() = default;

    CreatureModifier(Game& game, Creature& creature) : game(game), creature(creature)
    {
    }
};

class AddDefenceModifier : public CreatureModifier
{
    boost::signals2::connection conn;

   public:
    AddDefenceModifier(Game& game, Creature& creature) : CreatureModifier(game, creature)
    {
        conn = game.queries.connect([&](StatQuery& sq, Creature& other) {
            if (&other != &creature && sq.statistic == StatQuery::Statistic::defense)
                sq.result += 1;
        });
    }

    ~AddDefenceModifier()
    {
        conn.disconnect();
    }
};

class AddAttackModifier : public CreatureModifier
{
    boost::signals2::connection conn;

   public:
    AddAttackModifier(Game& game, Creature& creature) : CreatureModifier(game, creature)
    {
        conn = game.queries.connect([&](StatQuery& sq, Creature& other) {
            if (&other != &creature && sq.statistic == StatQuery::Statistic::attack)
                sq.result += 1;
        });
    }

    ~AddAttackModifier()
    {
        conn.disconnect();
    }
};

struct Creature
{
   protected:
    Game& game;
    int base_attack, base_defense;

   public:
    Creature(Game& game, int base_attack, int base_defense) : game(game), base_attack(base_attack), base_defense(base_defense)
    {
    }
    virtual ~Creature() = default;
    virtual int get_attack() = 0;
    virtual int get_defense() = 0;
};

class Goblin : public Creature
{
   protected:
    std::vector<std::unique_ptr<CreatureModifier>> modifiers;

   public:
    Goblin(Game& game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense)
    {
        modifiers.push_back(std::make_unique<AddDefenceModifier>(game, *this));
    }

    Goblin(Game& game) : Goblin(game, 1, 1)
    {
    }

    virtual ~Goblin()
    {
    }

    int get_attack() override
    {
        StatQuery sq{StatQuery::Statistic::attack, base_attack};
        game.queries(sq, *this);
        return sq.result;
    }

    int get_defense() override
    {
        StatQuery sq{StatQuery::Statistic::defense, base_defense};
        game.queries(sq, *this);
        return sq.result;
    }
};

class GoblinKing : public Goblin
{
   public:
    GoblinKing(Game& game) : Goblin(game, 3, 3)
    {
        modifiers.push_back(std::make_unique<AddAttackModifier>(game, *this));
    }
};

int main()
{
    Game game;
    Goblin goblin_1{game};
    Goblin goblin_2{game};
    GoblinKing goblin_king{game};
    std::cout << "Goblin has attack: " << goblin_1.get_attack() << " and defense: " << goblin_1.get_defense() << std::endl;
    std::cout << "GoblinKing has attack: " << goblin_king.get_attack() << " and defense: " << goblin_king.get_defense() << std::endl;
    return 0;
}