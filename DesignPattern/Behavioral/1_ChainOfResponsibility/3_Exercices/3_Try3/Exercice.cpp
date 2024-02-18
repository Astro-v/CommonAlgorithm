#include <iostream>
#include <vector>

struct StatQuery
{
    enum Statistic
    {
        attack,
        defense
    } statistic;
    int result;
};

class Creature;
struct Game
{
    std::vector<Creature*> creatures;
};

class Creature
{
   protected:
    Game& game;
    int base_attack, base_defense;

   public:
    Creature(Game& game, int base_attack, int base_defense) : game(game), base_attack(base_attack), base_defense(base_defense)
    {
    }
    virtual int get_attack() = 0;
    virtual int get_defense() = 0;
    virtual void quiery(Creature* Creature, StatQuery& sq) = 0;
};

class Goblin : public Creature
{
   public:
    Goblin(Game& game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense)
    {
    }

    Goblin(Game& game) : Creature(game, 1, 1)
    {
    }

    int get_attack() override
    {
        StatQuery sq{StatQuery::Statistic::attack, base_attack};
        for (auto c : game.creatures)
        {
            c->quiery(this, sq);
        }
        return sq.result;
    }

    int get_defense() override
    {
        StatQuery sq{StatQuery::Statistic::defense, base_defense};
        for (auto c : game.creatures)
        {
            c->quiery(this, sq);
        }
        return sq.result;
    }

    void quiery(Creature* creature, StatQuery& sq)
    {
        if (sq.statistic == StatQuery::Statistic::defense && creature != this)
        {
            sq.result += 1;
        }
    }
};

class GoblinKing : public Goblin
{
   public:
    GoblinKing(Game& game) : Goblin(game, 3, 3)
    {
    }

    void quiery(Creature* creature, StatQuery& sq)
    {
        if (sq.statistic == StatQuery::Statistic::attack && creature != this)
        {
            sq.result += 1;
        }
        Goblin::quiery(creature, sq);
    }
};

int main()
{
    Game game;
    Goblin goblin_1{game};
    Goblin goblin_2{game};
    GoblinKing goblin_king{game};

    game.creatures.push_back(&goblin_1);
    game.creatures.push_back(&goblin_2);
    game.creatures.push_back(&goblin_king);
    std::cout << "Goblin has attack: " << goblin_1.get_attack() << " and defense: " << goblin_1.get_defense() << std::endl;
    std::cout << "GoblinKing has attack: " << goblin_king.get_attack() << " and defense: " << goblin_king.get_defense() << std::endl;
    return 0;
}