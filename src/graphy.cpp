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
#include "commands/echo.cpp"
#include "commands/saddsmembers.cpp"

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
        string c5 = c.substr(0, 5);
        string c6 = c.substr(0, 6);
        string c8 = c.substr(0, 8);
        string c9 = c.substr(0, 9);

        try
        {
            if (to_lower(c9) == "sismember") return sismember(c.substr(9), db);
            if (to_lower(c8) == "smembers") return smembers(c.substr(8), db);
            if (to_lower(c8) == "renamenx") return renamenx(c.substr(8), db);
            if (to_lower(c6) == "getset") return getset(c.substr(6), db, &debug);
            if (to_lower(c6) == "exists") return exists(c.substr(6), db);
            if (to_lower(c6) == "dbsize") return dbsize(c.substr(6), db, &debug);
            if (to_lower(c6) == "decrby") return decrby(c.substr(6), db);
            if (to_lower(c6) == "incrby") return incrby(c.substr(6), db);
            if (to_lower(c6) == "rename") return rename(c.substr(6), db);
            if (to_lower(c5) == "scard") return scard(c.substr(5), db);
            if (to_lower(c4) == "incr") return incr(c.substr(4), db);
            if (to_lower(c4) == "sadd") return sadd(c.substr(4), db);
            if (to_lower(c4) == "decr") return decr(c.substr(4), db);
            if (to_lower(c4) == "echo") return echo(c.substr(4));
            if (to_lower(c4) == "ping") return "PONG";
            if (to_lower(c4) == "quit") return "OK";
            if (to_lower(c4) == "save") return save(c.substr(4), db, &debug);
            if (to_lower(c3) == "get") return get(c.substr(3), db);
            if (to_lower(c3) == "set") return set(c.substr(3), db, &debug);
            if (to_lower(c3) == "del") return del(c.substr(3), db);
        }
        catch (const std::out_of_range)
        {
            return "ERR string out of range";
        }

        return "ERR unknown command";
    }

    string to_lower(string s)
    {
        for(char &c : s)
            c = tolower(c);
        return s;
    }
};