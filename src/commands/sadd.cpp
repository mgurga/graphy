#include "../graphy.h"

string Graphy::sadd(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() < 2) return ERR_NUM_OF_ARGS;
    int fails = 0;
    for (int i = 1; i < args.size(); i++)
        if (!db->sismember(args.at(0), args.at(i)))
            db->sadd(args.at(0), args.at(i));
        else
            fails++;
    return "(integer) " + to_string((args.size() - 1) - fails);
}
