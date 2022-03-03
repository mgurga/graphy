#include "../graphy.h"

string Graphy::randomkey(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 0) return ERR_NUM_OF_ARGS;
    return db->randomkey();
}
