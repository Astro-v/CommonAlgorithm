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
    function<string()> func;
    
    RedFlower(Flower& flower) : func([&flower](){ostringstream oss;
        oss << flower.str() << " and red";
        return oss.str();}) {}

    RedFlower(Rose& flower) : func([&flower](){ostringstream oss;
        oss << flower.str() << " that is red";
        return oss.str();}) {}

    RedFlower(RedFlower& flower) : func([&flower](){ostringstream oss;
        oss << flower.str();
        return oss.str();}) {}

    string str() override {
        return func();
    }
};

struct BlueFlower : Flower
{
    function<string()> func;
    
    BlueFlower(Flower& flower) : func([&flower](){ostringstream oss;
        oss << flower.str() << " and blue";
        return oss.str();}) {}

    BlueFlower(Rose& flower) : func([&flower](){ostringstream oss;
        oss << flower.str() << " that is blue";
        return oss.str();}) {}

    BlueFlower(BlueFlower& flower) : func([&flower](){ostringstream oss;
        oss << flower.str();
        return oss.str();}) {}

    string str() override {
        return func();
    }
};