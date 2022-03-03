#include "../graphy.h"

string Graphy::smove(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 3) return ERR_NUM_OF_ARGS;

    if (db->smove(args.at(0), args.at(1), args.at(2)))
        return "(integer) 1";
    else
        return "(integer) 0";
}
