#include "exercise.h"

int sum(const vector<ContainsIntegers*> items)
{
    int result = 0;
    for (const auto& elem : items)
    {
        result += elem->sum();
    }
    return result;
}