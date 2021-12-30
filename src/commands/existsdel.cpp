#include <string>
#include <iostream>
#include <sstream>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "../database.cpp"
#endif

using namespace std;

inline string exists(string s, Database* db)
{
    if (s.empty()) return "ERR wrong number of arguments passed";
    s = s.substr(1);
    int successful = 0;

    stringstream ss (s);
    string item;

    while (getline (ss, item, ' '))
        if (db->key_exists(item))
            successful++;

    return "(integer) " + to_string(successful);
}

inline string del(string s, Database* db)
{
    if (s.empty()) return "ERR wrong number of arguments passed";
    s = s.substr(1);
    int successful = 0;

    stringstream ss (s);
    string item;

    while (getline (ss, item, ' '))
        if (db->delete_key(item))
            successful++;

    return "(integer) " + to_string(successful);
}