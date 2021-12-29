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
    if (*debug)
        cout << "setting '" << s.substr(1, split - 1) << "' to '" << s.substr(split + 1) << "'" << endl;
    db->set(s.substr(1, split - 1), s.substr(split + 1));
    return "OK";
}