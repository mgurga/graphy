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

inline string sinter(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() == 0) return "ERR incorrect number of arguments";
    Formatter f;
    if (args.size() == 1) return f.redis_list(db->smembers(args.at(0)));
    vector<string> vals = db->smembers(args.at(0));
    vector<string> out;

    for (int i = 1; i <= args.size() - 1; i++)
    {
        vector<string> mem = db->smembers(args.at(i));
        for (int a = 0; a < mem.size(); a++)
        {
            string ele = mem.at(a);
            for (int b = 0; b < vals.size(); b++)
                if (vals.at(b) == ele)
                    out.push_back(ele);
        }
    }

    return f.redis_list(out);
}

inline string sinterstore(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() <= 1) return "ERR incorrect number of arguments";
    Formatter f;
    if (args.size() == 2)
    {
        vector<string> out = db->smembers(args.at(0));
        for (string s : out)
            db->sadd(args.at(0), s);
        return "(integer) " + to_string(out.size());
    }
    vector<string> vals = db->smembers(args.at(1));
    vector<string> out;

    for (int i = 2; i <= args.size() - 1; i++)
    {
        vector<string> mem = db->smembers(args.at(i));
        for (int a = 0; a < mem.size(); a++)
        {
            string ele = mem.at(a);
            for (int b = 0; b < vals.size(); b++)
                if (vals.at(b) == ele)
                    out.push_back(ele);
        }
    }

    for (string s : out)
        db->sadd(args.at(0), s);
    return "(integer) " + to_string(out.size());
}

inline string sdiff(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() == 0) return "ERR incorrect number of arguments";
    Formatter f;
    if (args.size() == 1) return f.redis_list(db->smembers(args.at(0)));
    vector<string> vals = db->smembers(args.at(0));

    for (int i = 1; i <= args.size() - 1; i++)
    {
        vector<string> mem = db->smembers(args.at(i));
        for (int a = 0; a < mem.size(); a++)
        {
            string ele = mem.at(a);
            for (int b = 0; b < vals.size(); b++)
                if (vals.at(b) == ele)
                    vals.erase(vals.begin() + b);
        }
    }

    return f.redis_list(vals);
}

inline string sdiffstore(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() <= 1) return "ERR incorrect number of arguments";
    Formatter f;
    if (args.size() == 2)
    {
        vector<string> out = db->smembers(args.at(0));
        for (string s : out)
            db->sadd(args.at(0), s);
        return "(integer) " + to_string(out.size());
    }
    vector<string> vals = db->smembers(args.at(1));

    for (int i = 2; i <= args.size() - 1; i++)
    {
        vector<string> mem = db->smembers(args.at(i));
        for (int a = 0; a < mem.size(); a++)
        {
            string ele = mem.at(a);
            for (int b = 0; b < vals.size(); b++)
                if (vals.at(b) == ele)
                    vals.erase(vals.begin() + b);
        }
    }

    for (string s : vals)
        db->sadd(args.at(0), s);
    return "(integer) " + to_string(vals.size());
}