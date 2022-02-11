#include "../graphy.h"

string Graphy::lpush(string s, Database *db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() > 2) return "ERR incorrect number of arguments";
    if (args.size() == 2)
        return "(integer) " + to_string(db->lpush(args.at(0), args.at(1)));

    int lastsize = 0;
    for (int i = 1; i < args.size(); i++)
    {
        lastsize = db->lpush(args.at(0), args.at(i));
    }

    return "(integer) " + to_string(lastsize);
}

string Graphy::lrange(string s, Database *db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 3) return "ERR incorrect number of arguments";

    vector<string> items = db->lrange(args.at(0), stoi(args.at(1)), stoi(args.at(2)));

    Formatter f;
    return f.redis_list(items);
}
