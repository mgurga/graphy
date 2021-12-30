#include <string>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "../database.cpp"
#endif

using namespace std;

inline string incr(string s, Database* db)
{
    string key = s.substr(1);
    string val = db->get(key);
    if (db->key_exists(key))
        db->delete_key(key);
    int out = stoi(val, nullptr) + 1;
    db->set(key, to_string(out));
    return to_string(out);
}

inline string decr(string s, Database* db)
{
    string key = s.substr(1);
    string val = db->get(key);
    if (db->key_exists(key))
        db->delete_key(key);
    int out = stoi(val, nullptr) - 1;
    db->set(key, to_string(out));
    return to_string(out);
}