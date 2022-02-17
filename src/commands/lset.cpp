#include "../graphy.h"

string Graphy::lset(string s, Database *db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 3) return "ERR incorrect number of arguments";

    if (db->lset(args.at(0), stoi(args.at(1)), args.at(2)))
        return "OK";
    else
        return "ERR index out of range";
}
