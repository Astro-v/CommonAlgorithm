#include <iostream>
#include <string>
#include <vector>
using namespace std;

class CombinationLock
{
    vector<int> combination;

   public:
    string status;

    CombinationLock(const vector<int>& combination) : combination(combination)
    {
        status = "LOCKED";
    }

    void enter_digit(int digit)
    {
        if (status == "ERROR" || status == "LOCKED")
        {
            status = std::to_string(digit);
        }
        else
        {
            status += std::to_string(digit);
            if (status.length() == combination.size())
            {
                for (int i{0}; i < combination.size(); ++i)
                {
                    if (combination[i] != status[i] - '0')
                    {
                        status = "ERROR";
                        return;
                    }
                }
                status = "OPEN";
            }
        }
    }
};