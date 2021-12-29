#include <string>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "../database.cpp"
#endif

using namespace std;

inline string incr(string s, Database* db)
{
    string val = db->get(s.substr(1));
    int out = stoi(val, nullptr) + 1;
    db->set(s.substr(1), to_string(out));
    return to_string(out);
}

inline string decr(string s, Database* db)
{
    string val = db->get(s.substr(1));
    int out = stoi(val, nullptr) - 1;
    db->set(s.substr(1), to_string(out));
    return to_string(out);
}