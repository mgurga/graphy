#include <string>

#include "../graphy.h"

using namespace std;

string Graphy::get(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return "ERR incorrect number of arguments";
    return db->get(args.at(0));
}

string Graphy::set(string s, Database* db, bool* debug)
{
    if (s.empty()) return "ERR incorrect number of arguments";
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return "ERR incorrect number of arguments";
    string key = args.at(0);
    if (db->key_exists(key)) db->delete_key(key);
    if (*debug)
        cout << "setting '" << key << "' to '" << args.at(1) << "'" << endl;
    db->set(key, args.at(1));
    return "OK";
}

string Graphy::getset(string s, Database* db, bool* debug)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return "ERR incorrect number of arguments";
    if (*debug)
        cout << "getset command: '" << s << "'" << endl;
    string key = args.at(0);
    if (*debug)
        cout << "detected key is: '" << key << "'";
    string getres = db->get(key);
    db->delete_key(key);
    db->set(key, args.at(1));
    return getres;
}

string Graphy::mset(string s, Database* db, bool* debug)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 0 && args.size() % 2 != 0) return "ERR incorrect number of arguments";
    for (int i = 0; i < args.size(); i+=2)
    {
        if (*debug)
            cout << "setting: " << args.at(i) << " to: " << args.at(i + 1) << endl;
        db->set(args.at(i), args.at(i + 1));
    }
    return "OK";
}

string Graphy::mget(string s, Database* db, bool* debug)
{
    Parser p;
    vector<string> args = p.parse(s);
    vector<string> out;
    if (args.size() == 0) return "ERR incorrect number of arguments";
    for (int i = 0; i < args.size(); i++)
    {
        if (*debug)
            cout << "getting: " << args.at(i) << endl;
        out.push_back(db->get(args.at(i)));
    }
    Formatter f;
    return f.redis_list(out);
}

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

string Graphy::renamenx(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return "ERR incorrect number of arguments";
    if (!db->key_exists(args.at(0))) return "ERR no such key";
    if (db->key_exists(args.at(1))) return "(integer) 0";
    string val = db->get(args.at(0));
    db->delete_key(args.at(0));
    if (db->key_exists(args.at(1)))
        db->delete_key(args.at(1));
    db->set(args.at(1), val);
    return "(integer) 1";
}
