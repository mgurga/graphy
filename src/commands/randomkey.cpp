#include "../graphy.h"

string Graphy::randomkey(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 0) return "ERR incorrect number of arguments";
    return db->randomkey();
}
