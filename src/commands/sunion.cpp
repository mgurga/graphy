#include "../graphy.h"

string Graphy::sunion(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() == 0) return ERR_NUM_OF_ARGS;
    Utils f;
    if (args.size() == 1) return f.redis_list(db->smembers(args.at(0)));

    vector<string> out;

    for (string set : args)
    {
        vector<string> smem = db->smembers(set);
        for (string s : smem)
            if (count(out.begin(), out.end(), s) == 0)
                out.push_back(s);
    }

    return f.redis_list(out);
}

string Graphy::sunionstore(string s, Database* db)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() <= 1) return ERR_NUM_OF_ARGS;
    Utils f;
    if (db->key_exists(args.at(0)))
        db->delete_key(args.at(0));
    if (args.size() == 2)
    {
        vector<string> out = db->smembers(args.at(1));
        for (string s : out)
            db->sadd(args.at(0), s);
        return "(integer) " + to_string(out.size());
    }

    vector<string> out;

    for (int i = 1; i < args.size(); i++)
    {
        vector<string> smem = db->smembers(args.at(i));
        for (string s : smem)
            if (count(out.begin(), out.end(), s) == 0)
                out.push_back(s);
    }

    for (string s : out)
        db->sadd(args.at(0), s);

    return "(integer) " + to_string(out.size());
}
