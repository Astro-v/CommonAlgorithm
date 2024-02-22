#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct IRat
{
    virtual void notify_change() = 0;
};

struct Game
{
    std::vector<IRat*> rats;
    void notify_change()
    {
        for (auto rat : rats)
        {
            rat->notify_change();
        }
    }
};

struct Rat : IRat
{
    Game& game;
    int attack{1};

    Rat(Game& game) : game(game)
    {
        game.rats.push_back(this);
        game.notify_change();
    }

    ~Rat()
    {
        auto it = std::find(game.rats.begin(), game.rats.end(), this);

        if (it != game.rats.end())
        {
            game.rats.erase(it);
        }
        game.notify_change();
    }

    void notify_change() override
    {
        attack = game.rats.size();
    }
};