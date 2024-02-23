#include <complex>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

struct DiscriminantStrategy
{
    virtual double calculate_discriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) override
    {
        return b * b - 4 * a * c;
    }
};

struct RealDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) override
    {
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
        {
            return nan("1");
        }
        return discriminant;
    }
};

class QuadraticEquationSolver
{
    DiscriminantStrategy& strategy;

   public:
    QuadraticEquationSolver(DiscriminantStrategy& strategy) : strategy(strategy)
    {
    }

    tuple<complex<double>, complex<double>> solve(double a, double b, double c)
    {
        double discriminant = strategy.calculate_discriminant(a, b, c);
        if (discriminant == nan("1"))
        {
            return {{nan("1")}, {nan("1")}};
        }

        complex<double> number = __complex_sqrt(complex<double>{discriminant});
        return {{(-b + number) / (2 * a)}, {(-b - number) / (2 * a)}};
    }
};