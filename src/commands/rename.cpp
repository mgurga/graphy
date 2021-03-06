#include "../graphy.h"

string Graphy::rename(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return ERR_NUM_OF_ARGS;
    if (!db->key_exists(args.at(0))) return ERR_NO_SUCH_KEY;
    string val = db->get(args.at(0));
    db->delete_key(args.at(0));
    if (db->key_exists(args.at(1)))
        db->delete_key(args.at(1));
    db->set(args.at(1), val);
    return "OK";
}

string Graphy::renamenx(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return ERR_NUM_OF_ARGS;
    if (!db->key_exists(args.at(0))) return ERR_NO_SUCH_KEY;
    if (db->key_exists(args.at(1))) return "(integer) 0";
    string val = db->get(args.at(0));
    db->delete_key(args.at(0));
    if (db->key_exists(args.at(1)))
        db->delete_key(args.at(1));
    db->set(args.at(1), val);
    return "(integer) 1";
}
