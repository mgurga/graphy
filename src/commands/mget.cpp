#include "../graphy.h"

string Graphy::mget(string s, Database* db, bool* debug)
{
    Parser p;
    vector<string> args = p.parse(s);
    vector<string> out;
    if (args.size() == 0) return "ERR incorrect number of arguments";
    for (int i = 0; i < args.size(); i++)
    {
        if (*debug)
            cout << "getting: " << args.at(i) << endl;
        out.push_back(db->get(args.at(i)));
    }
    Formatter f;
    return f.redis_list(out);
}
