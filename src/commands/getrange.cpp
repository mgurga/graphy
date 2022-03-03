#include "../graphy.h"

string Graphy::getrange(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 3) return "ERR incorrect number of arguments";
    string keyval = db->get(args.at(0));
    if (keyval == "(nil)")
        return "";
    int start = stoi(args.at(1));
    int end = stoi(args.at(2));

    if (start < 0)
        start = keyval.length() + start;
    if (end < 0)
        end = keyval.length() + end + 1;
    else
        end++;

    return keyval.substr(start, end);
}
