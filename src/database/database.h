#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <assert.h>
#include <iomanip>
#include <random>
#include <map>
#include <string.h>

using namespace std;

/*
  ----- START -----
  "GRAPHY" - 6 bytes magic value
  0x01 - 1 byte version number
  ----- KEY VALUE ENTRY -----
  0xEE - 1 byte beginning code
  x bytes - key
  0xEF - 1 byte metadata flag
  4 bytes - unsigned int denoting key value pair, set, or list
            (all 0x00s is a simple key value pair)
            (0x00 0x00 0x00 0x01 (1) is a set value)
            list index numbers start at 0x00 0x00 0x00 0x02 (2)
TODO: this flag wastes 3 bytes if the value is a key value pair or set
  0xFF - 1 byte seperation character
  x bytes - value
  ----- REPEAT KEY VALUE ENTRY -----
*/

#define BEG (char)0xEE
#define META (char)0xEF
#define VAL (char)0xFF
#define META_SIZE 4

enum KeyType {
    KeyValue,
    Set,
    List
};

class DBEntry
{
public:
    string key;
    int metadata;
    string value;
    int keystart;
    KeyType keytype;

    DBEntry();
    DBEntry(string key, string val, uint meta);

    friend ostream& operator<<(ostream &out, const DBEntry& data);
    friend bool operator==(const DBEntry& a, const DBEntry& b);
    int entry_size();
};

class Database
{
public:
    vector<char> data;
    bool* debug;
    mt19937 gen;

    Database(bool* d);

    void set(string key, string value);
    void sadd(string setname, string value);
    string get(string key);
    bool key_exists(string key);
    bool delete_key(string key);
    string save(string filename);
    KeyType key_type(string key);
    vector<string> smembers(string setname);
    bool sismember(string setname, string val);
    string srandmember(string setname);
    string randomkey();
    bool smove(string from, string to, string member);
    int key_start_index(string key);
    map<int, string> key_start_index_multi(string key = "");
    int keys();
    bool srem(string setname, string val);
    vector<DBEntry> get_key_data(string key = "");
    void flushdb();
    void add_dbentry(DBEntry dbe);
    bool delete_dbentry(DBEntry dbe);
    int lpush(string list, string val);
    int rpush(string list, string val);
    vector<string> lrange(string list, int start, int stop);

    void print_hex(int i);
    void print_string_bytes(string s);
    unsigned int to_int(unsigned char bytes[META_SIZE]);
    void to_bytes(unsigned int i, unsigned char* arr);
};
