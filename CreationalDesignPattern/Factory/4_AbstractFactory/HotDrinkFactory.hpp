#pragma once
#include "HotDrink.hpp"

struct HotDrinkFactory
{
    virtual unique_ptr<HotDrink> make() const = 0;
};