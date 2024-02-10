#include <string>
using namespace std;

struct Person
{
    int id;
    string name;
};

class PersonFactory
{
    int _instances_nbr = 0;

   public:
    Person create_person(const string& name)
    {
        return {_instances_nbr++, name};
    }
};