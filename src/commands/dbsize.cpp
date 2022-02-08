#include "../graphy.h"

string Graphy::dbsize(string s, Database* db, bool* debug)
{
    if (!s.empty()) return "ERR incorrect number of arguments";
    return "(integer) " + to_string(db->keys());
}
