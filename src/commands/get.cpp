#include <string>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "../database.cpp"
#endif

using namespace std;

inline string get(string s, Database* db) {
    if (s.empty()) return "ERR";
    return db->get(s.substr(1));
}