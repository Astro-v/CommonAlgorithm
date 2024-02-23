#include <complex>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

struct Creature
{
    int attack, health;

    Creature(int attack, int health) : attack(attack), health(health)
    {
    }
};

struct CardGame
{
    vector<Creature> creatures;

    CardGame(const vector<Creature>& creatures) : creatures(creatures)
    {
    }

    // return the index of the creature that won (is a live)
    // example:
    // - creature1 alive, creature2 dead, return creature1
    // - creature1 dead, creature2 alive, return creature2
    // - no clear winner: return -1
    int combat(int creature1, int creature2)
    {
        hit(creatures[creature1], creatures[creature2]);
        hit(creatures[creature2], creatures[creature1]);
        bool c1_alive = creatures[creature1].health > 0;
        bool c2_alive = creatures[creature2].health > 0;
        if (c1_alive == c2_alive)
            return -1;
        return c1_alive ? creature1 : creature2;
    }

    virtual void hit(Creature& attacker, Creature& other) = 0;
};

struct TemporaryCardDamageGame : CardGame
{
    TemporaryCardDamageGame(const vector<Creature>& creatures) : CardGame(creatures)
    {
    }

    void hit(Creature& attacker, Creature& other) override
    {
        if (attacker.attack >= other.health)
            other.health = 0;
    }
};

struct PermanentCardDamageGame : CardGame
{
    PermanentCardDamageGame(const vector<Creature>& creatures) : CardGame(creatures)
    {
    }

    void hit(Creature& attacker, Creature& other) override
    {
        if (attacker.attack >= other.health)
        {
            other.health = 0;
        }
        else
        {
            other.health -= attacker.attack;
        }
    }
};