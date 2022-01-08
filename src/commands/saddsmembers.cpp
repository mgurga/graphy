#include <string>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "../database.cpp"
#endif

#ifndef PARSER_CPP
#define PARSER_CPP
#include "../parser.cpp"
#endif

#ifndef FORMATTER_CPP
#define FORMATTER_CPP
#include "../formatter.cpp"
#endif

using namespace std;

inline string sadd(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() < 2) return "ERR incorrect number of arguments";
    int fails = 0;
    for (int i = 1; i < args.size(); i++)
        if (!db->sismember(args.at(0), args.at(i)))
            db->sadd(args.at(0), args.at(i));
        else
            fails++;
    return "(integer) " + to_string((args.size() - 1) - fails);
}

inline string sismember(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return "ERR incorrect number of arguments";
    return (db->sismember(args.at(0), args.at(1))) ? "(integer) 1" : "(integer) 0";
}

inline string scard(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return "ERR incorrect number of arguments";
    vector<string> mem = db->smembers(args.at(0));
    return "(integer) " + to_string(mem.size());
}

inline string smembers(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return "ERR incorrect number of arguments";
    vector<string> mem = db->smembers(args.at(0));
    Formatter f;
    return f.redis_list(mem);
}