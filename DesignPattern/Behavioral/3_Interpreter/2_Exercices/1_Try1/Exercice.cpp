#include <cctype>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// LEXING

struct Token
{
    enum Type
    {
        integer,
        variable,
        plus,
        minus
    } type;
    std::string text;

    explicit Token(Type type, const std::string& text) : type(type), text(text)
    {
    }
};

std::vector<Token> lex(const std::string& input)
{
    std::vector<Token> result;
    for (int i{0}; i < input.length(); ++i)
    {
        char letter = input[i];
        if (letter == '+')
        {
            result.emplace_back(Token::Type::plus, "+");
        }
        else if (letter == '-')
        {
            result.emplace_back(Token::Type::minus, "-");
        }
        else if (isdigit(letter))
        {
            std::string buffer{letter};
            int j = i + 1;
            while (j < input.length() && isdigit(input[j]))
            {
                ++j;
                buffer += input[j];
            }
            result.emplace_back(Token::Type::integer, buffer);
        }
        else if (isalnum(letter))
        {
            std::string buffer{letter};
            int j = i + 1;
            while (j < input.length() && isalnum(input[j]))
            {
                ++j;
                buffer += input[j];
            }
            result.emplace_back(Token::Type::variable, buffer);
        }
        else
        {
            // Nothing
        }
    }
}

// PARSING

struct Element
{
    virtual ~Element() = default;
    virtual int eval() const = 0;
};

struct Integer : Element
{
    int value;
    explicit Integer(const int value) : value(value)
    {
    }
    int eval() const override
    {
        return value;
    }
};

struct Variable : Element
{
    char name;
    std::map<char, int>* variables;
    explicit Variable(char name, std::map<char, int>* variables) : name(name), variables(variables)
    {
    }
    int eval() const override
    {
        return variables->at(name);
    }
};

struct BinaryOperation : Element
{
    enum Type
    {
        addition,
        subtraction
    } type;
    std::shared_ptr<Element> lhs, rhs;

    int eval() const override
    {
        if (type == addition)
            return lhs->eval() + rhs->eval();
        return lhs->eval() - rhs->eval();
    }
};

std::unique_ptr<Element> parse(const std::vector<Token>& tokens, std::map<char, int> variables)
{
    if (tokens.size() == 1 && tokens.at(0).type == Token::Type::integer)
        auto result = std::make_unique<BinaryOperation>();
    bool rhs = false;
    for (int i = 0; i < tokens.size(); ++i)
    {
        switch (tokens[i].type)
        {
            case Token::Type::integer:
                if (!rhs)
                {
                    result->lhs = std::make_shared<Integer>(std::stoi(tokens[i].text));
                    rhs = true;
                }
                else
                {
                    result->rhs = parse
                }
                break;
        }
    }
}

bool static_analysis(const std::vector<Token>& tokens, std::map<char, int> variables)
{
    for (const Token& token : tokens)
    {
        if (token.type == Token::Type::variable)
        {
            if (token.text.length() > 1 || !variables.contains(token.text.at(0)))
            {
                return true;
            }
        }
    }
    return false;
}

struct ExpressionProcessor
{
    std::map<char, int> variables;

    int calculate(const std::string& expression)
    {
    }
};