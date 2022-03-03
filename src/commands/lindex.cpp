#include "../graphy.h"

string Graphy::lindex(string s, Database *db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return ERR_NUM_OF_ARGS;

    return db->lindex(args.at(0), stoi(args.at(1)));
}
