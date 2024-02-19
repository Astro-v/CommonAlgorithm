#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Sentence
{
    struct WordToken
    {
        std::string plain_text;
        bool capitalize;

        std::string str() const
        {
            std::string s;
            for (size_t i = 0; i < plain_text.length(); ++i)
            {
                auto c = plain_text[i];
                if (capitalize)
                    c = toupper(c);
                s += c;
            }
            return s;
        }
    };

    std::vector<WordToken> words;

    Sentence(const std::string& text)
    {
        std::string token;
        std::istringstream iss(text);
        while (getline(iss, token, ' '))
            words.emplace_back(WordToken{token, false});
    }

    WordToken& operator[](size_t index)
    {
        return words[index];
    }

    std::string str() const
    {
        std::ostringstream oss;
        for (auto it = begin(words); it != end(words); ++it)
        {
            oss << it->str();
            if (it + 1 != end(words))
                oss << " ";
        }
        return oss.str();
    }
};

int main()
{
    Sentence sentence{"hello world"};
    sentence[1].capitalize = true;
    std::cout << sentence.str() << std::endl;
    return 0;
}