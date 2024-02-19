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

template <typename T, typename U>
bool contains(const std::map<T, U>& table, const T& elem)
{
    for (auto it = table.begin(); it != table.end(); ++it)
    {
        if (it->first == elem)
        {
            return true;
        }
    }
    return false;
}

struct ExpressionProcessor
{
    std::map<char, int> variables;

    std::vector<Token> lex(const std::string& input)
    {
        std::vector<Token> result;
        for (std::size_t i{0}; i < input.length(); ++i)
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
                std::size_t j = i + 1;
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
                std::size_t j = i + 1;
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
        return result;
    }

    std::shared_ptr<Element> parse(const std::vector<Token>& tokens)
    {
        if (tokens.size() == 1 && tokens.at(0).type == Token::Type::integer)
        {
            return std::make_shared<Integer>(std::stoi(tokens.at(0).text));
        }
        else if (tokens.size() == 1 && tokens.at(0).type == Token::Type::variable)
        {
            return std::make_shared<Variable>(tokens.at(0).text.at(0), &variables);
        }

        auto result = std::make_shared<BinaryOperation>();
        bool rhs = false;
        for (auto it = tokens.rbegin(); it != tokens.rend(); ++it)
        {
            switch (it->type)
            {
                case Token::Type::integer:
                    if (!rhs)
                    {
                        result->lhs = std::make_shared<Integer>(std::stoi(it->text));
                        rhs = true;
                    }
                    else
                    {
                        result->rhs = parse({it, tokens.rend()});
                        it = tokens.rend() - 1;
                    }
                    break;
                case Token::Type::variable:
                    if (!rhs)
                    {
                        result->lhs = std::make_shared<Variable>(it->text.at(0), &variables);
                        rhs = true;
                    }
                    else
                    {
                        result->rhs = parse({it, tokens.rend()});
                        it = tokens.rend() - 1;
                    }
                    break;
                case Token::Type::plus:
                    result->type = BinaryOperation::addition;
                    break;
                case Token::Type::minus:
                    result->type = BinaryOperation::subtraction;
                    break;
            }
        }
        return result;
    }

    bool static_analysis(const std::vector<Token>& tokens)
    {
        for (auto token : tokens)
        {
            if (token.type == Token::Type::variable)
            {
                if (token.text.length() > 1 || !contains(variables, token.text.at(0)))
                {
                    return true;
                }
            }
        }
        return false;
    }

    int calculate(const std::string& expression)
    {
        auto lexing = lex(expression);
        if (static_analysis(lexing))
            return 0;
        return parse(lexing)->eval();
    }
};

int main()
{
    ExpressionProcessor ep;
    ep.variables['x'] = 10;
    ep.variables['t'] = 4;
    std::cout << ep.calculate("1+4+6-x+t") << std::endl;
}