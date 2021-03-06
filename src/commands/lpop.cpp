#include "../graphy.h"

string Graphy::lpop(string s, Database *db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return ERR_NUM_OF_ARGS;

    vector<string> keys = db->lpop(args.at(0));
    if (keys.empty())
        return "(nil)";
    else
        return keys.at(0);
}
