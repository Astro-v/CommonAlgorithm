#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct AdditionExpression;
struct MultiplicationExpression;
struct Value;

struct ExpressionVisitor
{
    virtual void accept(AdditionExpression& ae) = 0;
    virtual void accept(MultiplicationExpression& me) = 0;
    virtual void accept(Value& v) = 0;
};

struct Expression
{
    virtual void visit(ExpressionVisitor& ev) = 0;
};

template <typename T>
struct ExpressionCRTP : Expression
{
    void visit(ExpressionVisitor& ev) override
    {
        ev.accept(static_cast<T&>(*this));
    }
};

struct Value : ExpressionCRTP<Value>
{
    int value;

    Value(int value) : value(value)
    {
    }
};

struct AdditionExpression : ExpressionCRTP<AdditionExpression>
{
    Expression &lhs, &rhs;

    AdditionExpression(Expression& lhs, Expression& rhs) : lhs(lhs), rhs(rhs)
    {
    }

    AdditionExpression(Expression&& lhs, Expression&& rhs) : lhs(lhs), rhs(rhs)
    {
    }
};

struct MultiplicationExpression : ExpressionCRTP<MultiplicationExpression>
{
    Expression &lhs, &rhs;

    MultiplicationExpression(Expression& lhs, Expression& rhs) : lhs(lhs), rhs(rhs)
    {
    }

    MultiplicationExpression(Expression&& lhs, Expression&& rhs) : lhs(lhs), rhs(rhs)
    {
    }
};

struct ExpressionPrinter : ExpressionVisitor
{
    ostringstream oss;
    void accept(AdditionExpression& ae) override
    {
        oss << "(";
        ae.lhs.visit(*this);
        oss << "+";
        ae.rhs.visit(*this);
        oss << ")";
    }

    void accept(MultiplicationExpression& me) override
    {
        me.lhs.visit(*this);
        oss << "*";
        me.rhs.visit(*this);
    }

    void accept(Value& v) override
    {
        oss << v.value;
    }

    string str() const
    {
        return oss.str();
    }
};

int main()
{
    auto e = AdditionExpression{MultiplicationExpression{Value{10}, AdditionExpression{Value{3}, Value{5}}}, Value{4}};
    auto ep = ExpressionPrinter{};
    ep.accept(e);
    std::cout << ep.str() << std::endl;
}