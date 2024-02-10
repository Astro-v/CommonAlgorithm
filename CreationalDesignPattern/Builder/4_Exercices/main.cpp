#include <ostream>
#include <string>
#include <vector>
using namespace std;

class CodeElement
{
   private:
    string _name;
    string _type;

    const int _indent_size = 2;

   public:
    CodeElement(const string& name, const string& type) : _name(name), _type(type)
    {
    }

    friend ostream& operator<<(ostream& os, const CodeElement& obj)
    {
        for (int i = 0; i < obj._indent_size; ++i)
            os << " ";
        os << obj._type << " " << obj._name << ";";
        return os;
    }
};

class CodeBuilder
{
   private:
    string _class_name;
    vector<CodeElement> _elements;

   public:
    CodeBuilder(const string& class_name)
    {
        _class_name = class_name;
    }

    CodeBuilder& add_field(const string& name, const string& type)
    {
        _elements.emplace_back(name, type);
        return *this;
    }

    friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
    {
        os << "class " << obj._class_name << endl;
        os << "{" << endl;
        for (const auto& e : obj._elements)
            os << e << endl;
        os << "};" << endl;
        return os;
    }
};