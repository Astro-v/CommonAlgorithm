#include <iostream>
#include <type_traits>
#include <vector>

struct Creature;
struct Game
{
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
    virtual int get_attack() = 0;
    virtual int get_defense() = 0;
    virtual std::string get_name() = 0;
};

class GoblinKing;
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
        int result = base_attack;
        for (auto c : game.creatures)
        {
            if (c != this && c->get_name() == "Gobelin King")
            {
                result += 1;
            }
        }
        return result;
    }

    int get_defense() override
    {
        int result = base_defense;
        for (auto c : game.creatures)
        {
            if (c != this)
            {
                result += 1;
            }
        }
        return result;
    }

    std::string get_name() override
    {
        return "Gobelin";
    }
};

class GoblinKing : public Goblin
{
   public:
    GoblinKing(Game& game) : Goblin(game, 3, 3)
    {
    }

    std::string get_name() override
    {
        return "Gobelin King";
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