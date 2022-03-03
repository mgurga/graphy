#include "utils.h"

using namespace std;

Utils::Utils(bool d)
{
    debug = d;
}

string Utils::redis_list(vector<string> arr)
{
    if (arr.empty())
        return "(empty list or set)";
    string out;
    int index = 0;

    for (string &s : arr)
    {
        index++;
        out += to_string(index) + ") \"" + s + "\"\n";
    }

    out.pop_back();
    return out;
}

bool Utils::matches(string key, string pattern)
{
    replace_all(pattern, ".", "\\.");
    replace_all(pattern, "*", ".*");
    replace_all(pattern, "?", ".");
    regex re(pattern);
    return regex_match(key, re);
}

void Utils::replace_all(string& s, string const& toReplace, string const& replaceWith)
{
    ostringstream oss;
    size_t pos = 0;
    size_t prevPos;

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == string::npos)
            break;
        oss << s.substr(prevPos, pos - prevPos);
        oss << replaceWith;
        pos += toReplace.size();
    }

    oss << s.substr(prevPos);
    s = oss.str();
}
