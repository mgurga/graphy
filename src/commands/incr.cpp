#include "../graphy.h"

string Graphy::incr(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return "ERR incorrect number of arguments";
    string key = args.at(0);
    string val = db->get(key);
    if (db->key_exists(key))
        db->delete_key(key);
    int out = stoi(val, nullptr) + 1;
    db->set(key, to_string(out));
    return "(integer) " + to_string(out);
}

string Graphy::incrby(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return "ERR incorrect number of arguments";
    string key = args.at(0);
    string val = db->get(key);
    if (db->key_exists(key))
        db->delete_key(key);
    int out = stoi(val, nullptr) + stoi(args.at(1), nullptr);
    db->set(key, to_string(out));
    return "(integer) " + to_string(out);
}
