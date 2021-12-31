#include <string>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "../database.cpp"
#endif

using namespace std;

inline string get(string s, Database* db)
{
    if (s.empty()) return "ERR";
    return db->get(s.substr(1));
}

inline string set(string s, Database* db, bool* debug)
{
    if (s.empty()) return "ERR";
    int split = s.find(" ", 1);
    string key = s.substr(1, split - 1);
    if (db->key_exists(key)) db->delete_key(key);
    if (*debug)
        cout << "setting '" << key << "' to '" << s.substr(split + 1) << "'" << endl;
    db->set(key, s.substr(split + 1));
    return "OK";
}

inline string getset(string s, Database* db, bool* debug)
{
    s = s.substr(1);
    if (*debug)
        cout << "getset command: '" << s << "'" << endl;
    int split = s.find(" ");
    string key = s.substr(0, split);
    if (*debug)
        cout << "detected key is: '" << key << "'";
    string getres = db->get(key);
    db->delete_key(key);
    db->set(key, s.substr(split + 1));
    return getres;
}