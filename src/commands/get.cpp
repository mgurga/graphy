#include "../graphy.h"

string Graphy::get(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return "ERR incorrect number of arguments";
    return db->get(args.at(0));
}
