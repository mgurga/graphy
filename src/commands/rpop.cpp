#include "../graphy.h"

string Graphy::rpop(string s, Database *db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return "ERR incorrect number of arguments";

    vector<string> keys = db->rpop(args.at(0));
    if (keys.empty())
        return "(nil)";
    else
        return keys.at(0);
}
