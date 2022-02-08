#include "../graphy.h"

string Graphy::spop(string s, Database* db)
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
