#include "../graphy.h"

string Graphy::set(string s, Database* db, bool* debug)
{
    if (s.empty()) return ERR_NUM_OF_ARGS;
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return ERR_NUM_OF_ARGS;
    string key = args.at(0);
    if (db->key_exists(key)) db->delete_key(key);
    if (*debug)
        cout << "setting '" << key << "' to '" << args.at(1) << "'" << endl;
    db->set(key, args.at(1));
    return "OK";
}
