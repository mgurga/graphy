#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <regex>

using namespace std;

class Utils
{
public:
    bool debug;

    Utils(bool d = false);
    string redis_list(vector<string> arr);
    bool matches(string key, string pattern);
    void replace_all(string& s, string const& toReplace, string const& replaceWith);
};
