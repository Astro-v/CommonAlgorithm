#include <string>
#include <sstream>
#include <functional>
using namespace std;

struct Flower
{
    virtual string str() = 0;
};

struct Rose : Flower
{
    string str() override {
        ostringstream oss;
        oss << "A rose";
        return oss.str();
    }
};

struct RedFlower : Flower
{
    Flower& flower;
    function<string()> func;
    
    RedFlower(Flower& flower) : flower(flower), func([](){ostringstream oss;
        oss  << " and red";
        return oss.str();}) {}

    RedFlower(Rose& flower) : flower(flower), func([](){ostringstream oss;
        oss << " that is red";
        return oss.str();}) {}

    RedFlower(RedFlower& flower) : flower(flower), func([](){ostringstream oss;
        return oss.str();}) {}

    string str() override {
        static bool called = false;
        called = false;
        ostringstream oss;
        oss << flower.str();
        if (!called)
        {
            called = true;
            oss << func();
        }
        return oss.str();
    }
};

struct BlueFlower : Flower
{
    Flower& flower;
    function<string()> func;
    
    BlueFlower(Flower& flower) : flower(flower),  func([](){ostringstream oss;
        oss << " and blue";
        return oss.str();}) {}

    BlueFlower(Rose& flower) : flower(flower),  func([](){ostringstream oss;
        oss << " that is blue";
        return oss.str();}) {}

    BlueFlower(BlueFlower& flower) : flower(flower), func([](){ostringstream oss;
        return oss.str();}) {}

    string str() override {
        static bool called = false;
        called = false;
        ostringstream oss;
        oss << flower.str();
        if (!called)
        {
            called = true;
            oss << func();
        }
        return oss.str();
    }
};