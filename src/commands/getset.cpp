#include "../graphy.h"

string Graphy::getset(string s, Database* db, bool* debug)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() != 2) return "ERR incorrect number of arguments";
    if (*debug)
        cout << "getset command: '" << s << "'" << endl;
    string key = args.at(0);
    if (*debug)
        cout << "detected key is: '" << key << "'";
    string getres = db->get(key);
    db->delete_key(key);
    db->set(key, args.at(1));
    return getres;
}
