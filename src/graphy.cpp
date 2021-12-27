#include <string>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "database.cpp"
#endif

#include "commands/get.cpp"
#include "commands/set.cpp"

using namespace std;

class Graphy {
public:
    Database* db;
    bool debug;

    Graphy(bool d = false) {
        db = new Database(&debug);
        debug = d;
    }

    string command(string c) {
        if (debug)
            cout << "got command: " << c << endl;

        if (c.substr(0, 4) == "ping") return "PONG";
        if (c.substr(0, 3) == "get") return get(c.substr(3), db);
        if (c.substr(0, 3) == "set") return set(c.substr(3), db, &debug);
        if (c.substr(0, 4) == "save") return db->save("backup.gdb");

        return "ERR";
    }
};