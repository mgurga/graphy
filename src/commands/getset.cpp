#include <string>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "../database.cpp"
#endif

#ifndef PARSER_CPP
#define PARSER_CPP
#include "../parser.cpp"
#endif

using namespace std;

inline string get(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return "ERR incorrect number of arguments";
    return db->get(s.substr(1));
}

inline string set(string s, Database* db, bool* debug)
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

inline string getset(string s, Database* db, bool* debug)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return "ERR incorrect number of arguments";
    if (*debug)
        cout << "getset command: '" << s << "'" << endl;
    int split = s.find(" ");
    string key = args.at(0);
    if (*debug)
        cout << "detected key is: '" << key << "'";
    string getres = db->get(key);
    db->delete_key(key);
    db->set(key, args.at(1));
    return getres;
}