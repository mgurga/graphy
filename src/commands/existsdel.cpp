#include <string>
#include <iostream>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "../database.cpp"
#endif

#ifndef PARSER_CPP
#define PARSER_CPP
#include "../parser.cpp"
#endif

using namespace std;

inline string exists(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() == 0) return "ERR incorrect number of arguments";
    int successful = 0;

    for (string item : args)
        if (db->key_exists(item))
            successful++;

    return "(integer) " + to_string(successful);
}

inline string del(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() == 0) return "ERR incorrect number of arguments";
    int successful = 0;

    for (string item : args)
        if (db->delete_key(item))
            successful++;

    return "(integer) " + to_string(successful);
}