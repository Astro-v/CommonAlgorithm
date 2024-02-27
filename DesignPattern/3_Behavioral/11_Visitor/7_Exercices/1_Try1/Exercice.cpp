#include <sstream>
#include <string>
using namespace std;

struct ExpressionVisitor
{
    virtual void accept(AdditionExpression* ae) = 0;
    virtual void accept(MultiplicationExpression* me) = 0;
    virtual void accept(Value* v) = 0;
};

struct Expression
{
    virtual void visit(ExpressionVisitor& ev) = 0;
};

struct Value : Expression
{
    int value;

    Value(int value) : value(value)
    {
    }

    void visit(ExpressionVisitor& ev) override
    {
        ev.accept(this);
    }
};

struct AdditionExpression : Expression
{
    Expression &lhs, &rhs;

    AdditionExpression(Expression& lhs, Expression& rhs) : lhs(lhs), rhs(rhs)
    {
    }

    void visit(ExpressionVisitor& ev) override
    {
        ev.accept(this);
    }
};

struct MultiplicationExpression : Expression
{
    Expression &lhs, &rhs;

    MultiplicationExpression(Expression& lhs, Expression& rhs) : lhs(lhs), rhs(rhs)
    {
    }

    void visit(ExpressionVisitor& ev) override
    {
        ev.accept(this);
    }
};

struct ExpressionPrinter : ExpressionVisitor
{
    ostringstream oss;

    void accept(AdditionExpression* ae) override;
    void accept(MultiplicationExpression* me) override;
    void accept(Value* v) override;

    string str() const
    { /* todo */
    }
};

void ExpressionPrinter::accept(AdditionExpression* ae)
{
}

void ExpressionPrinter::accept(MultiplicationExpression* me)
{
    me->lhs.visit(*this);
    oss << "*";
    me->rhs.visit(*this);
}

void ExpressionPrinter::accept(Value* v)
{
    oss << v->value;
}