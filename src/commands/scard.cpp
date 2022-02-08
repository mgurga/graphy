#include "../graphy.h"

string Graphy::scard(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return "ERR incorrect number of arguments";
    vector<string> mem = db->smembers(args.at(0));
    return "(integer) " + to_string(mem.size());
}
