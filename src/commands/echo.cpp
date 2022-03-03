#include "../graphy.h"

string Graphy::echo(string s)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() == 0 || args.size() > 1) return ERR_NUM_OF_ARGS;
    return args.at(0);
}
