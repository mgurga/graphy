#include "../graphy.h"

string Graphy::dbsize(string s, Database* db, bool* debug)
{
    if (!s.empty()) return ERR_NUM_OF_ARGS;
    return "(integer) " + to_string(db->keys());
}
