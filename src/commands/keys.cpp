#include "../graphy.h"

string Graphy::keys(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return ERR_NUM_OF_ARGS;
    vector<string> out;
    Utils u;
    for (DBEntry e : db->get_key_data())
    {
        if (u.matches(e.key, args.at(0)))
            out.push_back(e.key);
    }
    return u.redis_list(out);
}
