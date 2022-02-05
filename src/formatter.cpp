#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Formatter
{
public:
    bool debug;

    Formatter(bool d = false)
    {
        debug = d;
    }

    string redis_list(vector<string> arr)
    {
        if (arr.empty())
            return "empty array";
        string out;
        int index = 0;

        for (string s : arr)
        {
            index++;
            out += to_string(index) + ") \"" + s + "\"\n";
        }

        out.pop_back();
        return out;
    }
};
