#include <string>
#include <ctime>

#include "../graphy.h"

string Graphy::echo(string s)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() == 0 || args.size() > 1) return "ERR incorrect number of arguments";
    return args.at(0);
}

string Graphy::randomkey(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 0) return "ERR incorrect number of arguments";
    return db->randomkey();
}
