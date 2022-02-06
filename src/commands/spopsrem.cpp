#include <string>
#include <math.h>

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

inline string spop(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1 && args.size() != 2) return "ERR incorrect number of arguments";

    int count;
    if (args.size() == 2)
        count = abs(stoi(args.at(1), nullptr));
    else
        count = 1;

    if (count == 1)
    {
        string randval = db->srandmember(args.at(0));
        db->srem(args.at(0), randval);

        return "\"" + randval + "\"";
    } else {
        Formatter f;
        vector<string> out;

        for (int i = 0; i < count; i++)
        {
            string randval = db->srandmember(args.at(0));
            if (randval == "(nil)")
                continue;
            out.push_back(randval);
            db->srem(args.at(0), randval);
        }

        return f.redis_list(out);
    }
}

inline string srem(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return "ERR incorrect number of arguments";

    if (db->srem(args.at(0), args.at(1)))
        return "(integer) 1";
    else
        return "(integer) 0";
}

inline string srandmember(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 1 && args.size() != 2) return "ERR incorrect number of arguments";

    int count;
    if (args.size() == 2)
        count = abs(stoi(args.at(1), nullptr));
    else
        count = 1;

    if (count == 1)
        return "\"" + db->srandmember(args.at(0)) + "\"";
    else {
        Formatter f;
        vector<string> out;

        for (int i = 0; i < count; i++)
            out.push_back(db->srandmember(args.at(0)));

        return f.redis_list(out);
    }
}

inline string smove(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 3) return "ERR incorrect number of arguments";

    if (db->smove(args.at(0), args.at(1), args.at(2)))
        return "(integer) 1";
    else
        return "(integer) 0";
}
