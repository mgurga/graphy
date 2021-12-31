#include <string>
#include <locale>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "database.cpp"
#endif

#include "commands/getset.cpp"
#include "commands/save.cpp"
#include "commands/incrdecr.cpp"
#include "commands/existsdel.cpp"

using namespace std;

class Graphy
{
public:
    Database* db;
    bool debug;

    Graphy(bool d = false)
    {
        db = new Database(&debug);
        debug = d;
    }

    string command(string c)
    {
        if (debug)
            cout << "got command: " << c << endl;

        string c3 = c.substr(0, 3);
        string c4 = c.substr(0, 4);
        string c6 = c.substr(0, 6);

        if (to_lower(c6) == "getset") return getset(c.substr(6), db, &debug);
        if (to_lower(c6) == "exists") return exists(c.substr(6), db);
        if (to_lower(c4) == "incr") return incr(c.substr(4), db);
        if (to_lower(c4) == "decr") return decr(c.substr(4), db);
        if (to_lower(c4) == "ping") return "PONG";
        if (to_lower(c4) == "save") return save(c.substr(4), db, &debug);
        if (to_lower(c3) == "get") return get(c.substr(3), db);
        if (to_lower(c3) == "set") return set(c.substr(3), db, &debug);
        if (to_lower(c3) == "del") return del(c.substr(3), db);

        return "ERR unknown command";
    }

    string to_lower(string s)
    {
        for(char &c : s)
            c = tolower(c);
        return s;
    }
};