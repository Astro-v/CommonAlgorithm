#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

struct Logger
{
    function<void()> func;
    string name;

    Logger(const function<void()>& func, const string& name) : func{func}, name{name}
    {
    }

    void operator()() const
    {
        cout << "Entering " << name << endl;
        func();
        cout << "Exiting " << name << endl;
    }
};

template <typename Func>
struct Logger2
{
    Func func;
    string name;

    Logger2(const Func& func, const string& name) : func{func}, name{name}
    {
    }

    void operator()() const
    {
        cout << "Entering " << name << endl;
        func();
        cout << "Exiting " << name << endl;
    }
};

template <typename Func>
auto make_logger2(Func func, const string& name)
{
    return Logger2<Func>{func, name};
}

// need partial specialization for this to work
template <typename>
struct Logger3;

// return type and argument list
template <typename R, typename... Args>
struct Logger3<R(Args...)>
{
    Logger3(function<R(Args...)> func, const string& name) : func{func}, name{name}
    {
    }

    R operator()(Args... args)
    {
        cout << "Entering " << name << endl;
        R result = func(args...);
        cout << "Exiting " << name << endl;
        return result;
    }

    function<R(Args...)> func;
    string name;
};

template <typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const string& name)
{
    return Logger3<R(Args...)>(std::function<R(Args...)>(func), name);
}

double add(double a, double b)
{
    cout << a << "+" << b << "=" << (a + b) << endl;
    return a + b;
}

void function_decorator()
{
    // Logger([]() {cout << "Hello" << endl; }, "HelloFunction")();

    // cannot do this
    // make_logger2([]() {cout << "Hello" << endl; }, "HelloFunction")();
    auto call = make_logger2([]() { cout << "Hello!" << endl; }, "HelloFunction");
    call();

    auto logged_add = make_logger3(add, "Add");
    auto result = logged_add(2, 3);
}

int main()
{
    function_decorator();
    return 0;
}