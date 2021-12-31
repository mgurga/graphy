#include <string>
#include <ctime>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "../database.cpp"
#endif

#ifndef PARSER_CPP
#define PARSER_CPP
#include "../parser.cpp"
#endif

using namespace std;

inline string save(string s, Database* db, bool* debug) {
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