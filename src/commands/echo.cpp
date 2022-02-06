#include <string>
#include <ctime>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "../database.cpp"
#endif

#ifndef PARSER_CPP
#define PARSER_CPP
#include "../parser.cpp"
#endif

inline string echo(string s)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() == 0 || args.size() > 1) return "ERR incorrect number of arguments";
    return args.at(0);
}

inline string randomkey(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 0) return "ERR incorrect number of arguments";
    return db->randomkey();
}
