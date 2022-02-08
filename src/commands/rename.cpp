#include "../graphy.h"

string Graphy::rename(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return "ERR incorrect number of arguments";
    if (!db->key_exists(args.at(0))) return "ERR no such key";
    string val = db->get(args.at(0));
    db->delete_key(args.at(0));
    if (db->key_exists(args.at(1)))
        db->delete_key(args.at(1));
    db->set(args.at(1), val);
    return "OK";
}
