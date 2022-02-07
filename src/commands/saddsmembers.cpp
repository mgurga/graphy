#include <string>

#include "../graphy.h"

using namespace std;

string Graphy::sadd(string s, Database* db)
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

string Graphy::sismember(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return "ERR incorrect number of arguments";
    return (db->sismember(args.at(0), args.at(1))) ? "(integer) 1" : "(integer) 0";
}

string Graphy::scard(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return "ERR incorrect number of arguments";
    vector<string> mem = db->smembers(args.at(0));
    return "(integer) " + to_string(mem.size());
}

string Graphy::smembers(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1) return "ERR incorrect number of arguments";
    vector<string> mem = db->smembers(args.at(0));
    Formatter f;
    return f.redis_list(mem);
}
