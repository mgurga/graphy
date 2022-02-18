#include "../graphy.h"

string Graphy::lindex(string s, Database *db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return "ERR incorrect number of arguments";

    return db->lindex(args.at(0), stoi(args.at(1)));
}
