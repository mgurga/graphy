#include "../graphy.h"

string Graphy::sismember(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return "ERR incorrect number of arguments";
    return (db->sismember(args.at(0), args.at(1))) ? "(integer) 1" : "(integer) 0";
}
