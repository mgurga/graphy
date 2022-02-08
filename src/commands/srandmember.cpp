#include "../graphy.h"

string Graphy::srandmember(string s, Database* db)
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
