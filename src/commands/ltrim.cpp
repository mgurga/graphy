#include "../graphy.h"

string Graphy::ltrim(string s, Database *db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 3) return "ERR incorrect number of arguments";

    db->ltrim(args.at(0), stoi(args.at(1)), stoi(args.at(2)));
    return "OK";
}
