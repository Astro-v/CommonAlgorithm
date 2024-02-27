#pragma once
#include "HotDrinkFactory.hpp"

struct TeaFactory : HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Tea>();
    }
};