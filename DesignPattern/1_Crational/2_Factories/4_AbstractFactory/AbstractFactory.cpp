#include <iostream>
#include <map>
#include <memory>
#include "DrinkFactory.hpp"
#include "HotDrink.hpp"
using namespace std;

unique_ptr<HotDrink> make_drink(string type)
{
    unique_ptr<HotDrink> drink;
    if (type == "tea")
    {
        drink = make_unique<Tea>();
        drink->prepare(200);
    }
    else
    {
        drink = make_unique<Coffee>();
        drink->prepare(50);
    }
    return drink;
}

int main53()
{
    auto d = make_drink("tea");

    DrinkFactory df;
    df.make_drink("coffee");

    getchar();
    return 0;
}