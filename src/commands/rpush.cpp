#include "../graphy.h"

string Graphy::rpush(string s, Database *db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() < 2) return "ERR incorrect number of arguments";
    if (args.size() == 2)
        return "(integer) " + to_string(db->rpush(args.at(0), args.at(1)));

    int lastsize = 0;
    for (int i = 1; i < args.size(); i++)
        lastsize = db->rpush(args.at(0), args.at(i));

    return "(integer) " + to_string(lastsize);
}
