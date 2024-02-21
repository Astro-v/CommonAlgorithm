#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct Token
{
    int value;

    Token(int value) : value(value)
    {
    }
};

struct Memento
{
    vector<shared_ptr<Token>> tokens;

    Memento(vector<shared_ptr<Token>> tokens)
    {
        for (auto token : tokens)
        {
            Memento::tokens.push_back(std::make_shared<Token>(token->value));
        }
    }
};

struct TokenMachine
{
    vector<shared_ptr<Token>> tokens;

    Memento add_token(int value)
    {
        return add_token(make_shared<Token>(value));
    }

    // adds the token to the set of tokens and returns the
    // snapshot of the entire system
    Memento add_token(const shared_ptr<Token>& token)
    {
        tokens.push_back(token);
        return {tokens};
    }

    // reverts the system to a state represented by the token
    void revert(const Memento& m)
    {
        tokens = m.tokens;
    }
};