#include "../graphy.h"

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
