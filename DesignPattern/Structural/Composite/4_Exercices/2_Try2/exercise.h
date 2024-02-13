#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ContainsIntegers
{
    virtual int sum() = 0;
};

template <typename Self>
struct SomeIntegers : ContainsIntegers
{
    int sum() override
    {
        int result = 0;
        for (auto& item : static_cast<Self&>(*this))
        {
            result += item;
        }
        return result;
    }
};

struct SingleValue : SomeIntegers<SingleValue>
{
    int value{0};

    SingleValue() = default;

    explicit SingleValue(const int value) : value{value}
    {
    }

    int* begin()
    {
        return &value;
    }

    int* end()
    {
        return &value + 1;
    }
};

struct ManyValues : vector<int>, SomeIntegers<ManyValues>
{
    void add(const int value)
    {
        push_back(value);
    }
};

int sum(const vector<ContainsIntegers*> items);