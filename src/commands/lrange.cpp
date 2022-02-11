#include "../graphy.h"

string Graphy::lrange(string s, Database *db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 3) return "ERR incorrect number of arguments";

    vector<string> items = db->lrange(args.at(0), stoi(args.at(1)), stoi(args.at(2)));

    Formatter f;
    return f.redis_list(items);
}
