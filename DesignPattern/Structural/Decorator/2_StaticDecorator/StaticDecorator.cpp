#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Shape
{
    virtual string str() const = 0;
};

struct Circle : Shape
{
    float radius;

    Circle()
    {
    }

    explicit Circle(const float radius) : radius{radius}
    {
    }

    void resize(float factor)
    {
        radius *= factor;
    }

    string str() const override
    {
        ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Shape
{
    float side;

    Square()
    {
    }

    explicit Square(const float side) : side{side}
    {
    }

    string str() const override
    {
        ostringstream oss;
        oss << "A square of with side " << side;
        return oss.str();
    }
};

template <typename T>
concept IsShape = std::is_base_of<Shape, T>::value;

// note: class, not typename
template <IsShape T>
struct ColoredShape : T
{
    // One way to do this is to use a template specialization C++17
    // static_assert(is_base_of<Shape, T>::value, "Template argument must be a Shape");

    string color;

    // need this (or not!)
    ColoredShape()
    {
    }

    template <typename... Args>
    ColoredShape(const string& color, Args... args) : T(std::forward<Args>(args)...), color{color}
    // you cannot call base class ctor here
    // b/c you have no idea what it is
    {
    }

    string str() const override
    {
        ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};

template <IsShape T>
struct TransparentShape : T
{
    uint8_t transparency;

    template <typename... Args>
    TransparentShape(const uint8_t transparency, Args... args) : T(std::forward<Args>(args)...), transparency{transparency}
    {
    }

    string str() const override
    {
        ostringstream oss;
        oss << T::str() << " has " << static_cast<float>(transparency) / 255.f * 100.f << "% transparency";
        return oss.str();
    }
};

void mixin_inheritance()
{
    // won't work without a default constructor
    ColoredShape<Circle> green_circle{"green"};
    green_circle.radius = 123;
    cout << green_circle.str() << endl;

    TransparentShape<ColoredShape<Square>> blue_invisible_square{0};
    blue_invisible_square.color = "blue";
    blue_invisible_square.side = 321;
    cout << blue_invisible_square.str() << endl;
}


void constructor_forwarding()
{
    struct NotAShape
    {
        virtual string str() const
        {
            return string{};
        }
    };

    // we don't want this to be legal, thus a static_assert above
    // ColoredShape<NotAShape> legal;

    // no code completion for this case
    // can comment out argument, too! (default constructor)
    TransparentShape<Square> hidden_square{1, 2};
    cout << hidden_square.str() << endl;

    ColoredShape<TransparentShape<Square>> sq = {"red", 51, 5};
    cout << sq.str() << endl;
}

int main()
{
    mixin_inheritance();
    constructor_forwarding();
    return 0;
}