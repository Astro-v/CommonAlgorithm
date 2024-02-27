#pragma once
#include <memory>
#include "HotDrink.hpp"
#include "HotDrinkFactory.hpp"

struct HotDrink;

struct CoffeeFactory : HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Coffee>();
    }
};