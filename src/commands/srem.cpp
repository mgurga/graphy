#include "../graphy.h"

string Graphy::srem(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return ERR_NUM_OF_ARGS;

    if (db->srem(args.at(0), args.at(1)))
        return "(integer) 1";
    else
        return "(integer) 0";
}
