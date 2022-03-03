#include "../graphy.h"

string Graphy::llen(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return ERR_NUM_OF_ARGS;
    return "(integer) " + to_string(db->llen(args.at(0)));
}
