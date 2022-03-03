#include "../graphy.h"

string Graphy::mset(string s, Database* db, bool* debug)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 0 && args.size() % 2 != 0) return ERR_NUM_OF_ARGS;
    for (int i = 0; i < args.size(); i+=2)
    {
        if (*debug)
            cout << "setting: " << args.at(i) << " to: " << args.at(i + 1) << endl;
        db->set(args.at(i), args.at(i + 1));
    }
    return "OK";
}
