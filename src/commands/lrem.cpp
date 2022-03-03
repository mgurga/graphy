#include "../graphy.h"

string Graphy::lrem(string s, Database *db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 3) return ERR_NUM_OF_ARGS;

    return "(integer) " + to_string(db->lrem(args.at(0), stoi(args.at(1)), args.at(2)));
}
