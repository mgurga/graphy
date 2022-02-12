#include "../graphy.h"

string Graphy::llen(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return "ERR incorrect number of arguments";
    return "(integer) " + to_string(db->llen(args.at(0)));
}
