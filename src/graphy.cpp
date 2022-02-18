#include <string>
#include <locale>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "database/database.h"
#endif

#include "graphy.h"

using namespace std;

Graphy::Graphy(bool d)
{
    db = new Database(&debug);
    debug = d;
}

string Graphy::command(string c)
{
    if (debug)
        cout << "got command: " << c << endl;

    string c3 = to_lower(c.substr(0, 3));
    string c4 = to_lower(c.substr(0, 4));
    string c5 = to_lower(c.substr(0, 5));
    string c6 = to_lower(c.substr(0, 6));
    string c7 = to_lower(c.substr(0, 7));
    string c8 = to_lower(c.substr(0, 8));
    string c9 = to_lower(c.substr(0, 9));
    string c10 = to_lower(c.substr(0, 10));
    string c11 = to_lower(c.substr(0, 11));

    try
    {
        if (c11 == "sinterstore") return sinterstore(c.substr(11), db);
        if (c11 == "sunionstore") return sunionstore(c.substr(11), db);
        if (c11 == "srandmember") return srandmember(c.substr(11), db);
        if (c10 == "sdiffstore") return sdiffstore(c.substr(10), db);
        if (c9 == "randomkey") return randomkey(c.substr(9), db);
        if (c9 == "sismember") return sismember(c.substr(9), db);
        if (c8 == "smembers") return smembers(c.substr(8), db);
        if (c8 == "renamenx") return renamenx(c.substr(8), db);
        if (c7 == "flushdb") return flushdb(db);
        if (c6 == "getset") return getset(c.substr(6), db, &debug);
        if (c6 == "exists") return exists(c.substr(6), db);
        if (c6 == "dbsize") return dbsize(c.substr(6), db, &debug);
        if (c6 == "decrby") return decrby(c.substr(6), db);
        if (c6 == "incrby") return incrby(c.substr(6), db);
        if (c6 == "sinter") return sinter(c.substr(6), db);
        if (c6 == "sunion") return sunion(c.substr(6), db);
        if (c6 == "rename") return rename(c.substr(6), db);
        if (c6 == "lrange") return lrange(c.substr(6), db);
        if (c6 == "lindex") return lindex(c.substr(6), db);
        if (c5 == "scard") return scard(c.substr(5), db);
        if (c5 == "sdiff") return sdiff(c.substr(5), db);
        if (c5 == "smove") return smove(c.substr(5), db);
        if (c5 == "lpush") return lpush(c.substr(5), db);
        if (c5 == "rpush") return rpush(c.substr(5), db);
        if (c4 == "srem") return srem(c.substr(4), db);
        if (c4 == "llen") return llen(c.substr(4), db);
        if (c4 == "lrem") return lrem(c.substr(4), db);
        if (c4 == "lset") return lset(c.substr(4), db);
        if (c4 == "lpop") return lpop(c.substr(4), db);
        if (c4 == "rpop") return rpop(c.substr(4), db);
        if (c4 == "spop") return spop(c.substr(4), db);
        if (c4 == "incr") return incr(c.substr(4), db);
        if (c4 == "mset") return mset(c.substr(4), db, &debug);
        if (c4 == "mget") return mget(c.substr(4), db, &debug);
        if (c4 == "sadd") return sadd(c.substr(4), db);
        if (c4 == "decr") return decr(c.substr(4), db);
        if (c4 == "echo") return echo(c.substr(4));
        if (c4 == "ping") return "PONG";
        if (c4 == "quit") return "OK";
        if (c4 == "save") return save(c.substr(4), db, &debug);
        if (c3 == "get") return get(c.substr(3), db);
        if (c3 == "set") return set(c.substr(3), db, &debug);
        if (c3 == "del") return del(c.substr(3), db);
    }
    catch (const char* message)
    {
        return "ERR string out of range with message: " + string(message);
    }

    return "ERR unknown command";
}

string Graphy::to_lower(string s)
{
    for(char &c : s)
        c = tolower(c);
    return s;
}
