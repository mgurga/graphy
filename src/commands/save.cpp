#include <string>
#include <ctime>

#include "../graphy.h"

using namespace std;

string Graphy::save(string s, Database* db, bool* debug)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() == 0) {
        time_t result = time(nullptr);
        string timestamp = string(asctime(localtime(&result)));
        timestamp.pop_back();
        if (*debug)
            cout << "setting timestamp: '" << timestamp << "'.gdb" << endl;
        return db->save(timestamp + ".gdb");
    } else
        return db->save(args.at(0) + ".gdb");
}

string Graphy::dbsize(string s, Database* db, bool* debug)
{
    if (!s.empty()) return "ERR incorrect number of arguments";
    return "(integer) " + to_string(db->keys());
}
