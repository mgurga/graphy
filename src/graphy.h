#ifndef GRAPHY_H
#define GRAPHY_H

#include <string>
#include <locale>
#include <algorithm>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "database/database.h"
#endif

#ifndef PARSER_CPP
#define PARSER_CPP
#include "parser.cpp"
#endif

#ifndef Utils_H
#define Utils_H
#include "utils.h"
#endif

#define ERR_NUM_OF_ARGS "ERR incorrect number of arguments"
#define ERR_UNKNOWN_COMMAND "ERR unknown command"
#define ERR_OUT_OF_RANGE "ERR out of range"
#define ERR_NO_SUCH_KEY "ERR no such key"

class Graphy
{
public:
    Database* db;
    bool debug;

    Graphy(bool d = false);
    string command(string c);
    string to_lower(string s);

    string echo(string s);
    string randomkey(string s, Database* db);
    string get(string s, Database* db);
    string set(string s, Database* db, bool* debug);
    string getset(string s, Database* db, bool* debug);
    string mset(string s, Database* db, bool* debug);
    string mget(string s, Database* db, bool* debug);
    string rename(string s, Database* db);
    string renamenx(string s, Database* db);
    string exists(string s, Database* db);
    string del(string s, Database* db);
    string sadd(string s, Database* db);
    string sismember(string s, Database* db);
    string scard(string s, Database* db);
    string smembers(string s, Database* db);
    string save(string s, Database* db, bool* debug);
    string dbsize(string s, Database* db, bool* debug);
    string incr(string s, Database* db);
    string incrby(string s, Database* db);
    string decr(string s, Database* db);
    string decrby(string s, Database* db);
    string sinter(string s, Database* db);
    string sinterstore(string s, Database* db);
    string sdiff(string s, Database* db);
    string sdiffstore(string s, Database* db);
    string spop(string s, Database* db);
    string srem(string s, Database* db);
    string srandmember(string s, Database* db);
    string smove(string s, Database* db);
    string sunion(string s, Database* db);
    string sunionstore(string s, Database* db);
    string flushdb(Database* db);
    string lpush(string s, Database* db);
    string lrange(string s, Database* db);
    string rpush(string s, Database* db);
    string llen(string s, Database* db);
    string lrem(string s, Database* db);
    string lset(string s, Database* db);
    string lpop(string s, Database* db);
    string rpop(string s, Database* db);
    string lindex(string s, Database* db);
    string ltrim(string s, Database* db);
    string getrange(string s, Database* db);
    string keys(string s, Database* db);
};
#endif // GRAPHY_H
