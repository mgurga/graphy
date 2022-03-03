#include "../graphy.h"

string Graphy::del(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() == 0) return ERR_NUM_OF_ARGS;
    int successful = 0;

    for (string& item : args)
        if (db->delete_key(item))
            successful++;

    return "(integer) " + to_string(successful);
}
