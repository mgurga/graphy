#include <iostream>
#include <unordered_map>
#include <string>
#include <string.h>
#include <iomanip>
#include <functional>
#include <vector>
#include <fstream>
#include <assert.h>
#include <iomanip>
#include <random>
#include <map>

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

    friend ostream& operator<< (ostream &out, DBEntry const& data)
    {
        out << "key: '" << data.key << "' metadata: " << data.metadata << " value: '" << data.value << "' key start index: " << data.keystart;
        return out;
    }

    int entry_size()
    {
        return key.length() + META_SIZE + value.length() + 1;
    }
};

class Database
{
public:
    vector<char> data;
    bool* debug;
    mt19937 gen;

    Database(bool* d)
    {
        // adds magic value and version
        char magic[7] = "GRAPHY";
        for (int i = 0; i < 6; i++)
            data.push_back(magic[i]);
        data.push_back((char)0x01);

        random_device rd;
        gen.seed(rd());

        debug = d;
    }

    void set(string key, string value)
    {
        if (*debug)
            cout << "key: '" << key << "' to value: '" << value << "'" << endl;
        // beginning byte
        data.push_back(BEG);

        // add key
        const char* ckey = key.data();
        int len = strlen(ckey);
        for (int i = 0; i < len; i++)
            data.push_back(ckey[i]);

        data.push_back(META);
        
        // add empty metadata
        for (int i = 0; i < META_SIZE; i++)
            data.push_back((char)0x00);

        data.push_back(VAL);

        // add value
        const char* cval = value.data();
        len = strlen(cval);
        for (int i = 0; i < len; i++)
            data.push_back(cval[i]);

        // save("test.gdb");
    }

    void sadd(string setname, string value)
    {
        if (*debug)
            cout << "key: '" << setname << "' to value: '" << value << "'" << endl;
        // beginning byte
        data.push_back(BEG);

        // add key
        const char* ckey = setname.data();
        int len = strlen(ckey);
        for (int i = 0; i < len; i++)
            data.push_back(ckey[i]);

        data.push_back(META);
        
        // add metadata
        unsigned char bytes[META_SIZE];
        to_bytes(1, bytes);
        for (int i = 0; i < META_SIZE; i++)
            data.push_back(bytes[i]);

        data.push_back(VAL);

        // add value
        const char* cval = value.data();
        len = strlen(cval);
        for (int i = 0; i < len; i++)
            data.push_back(cval[i]);

        // save("test.gdb");
    }

    string get(string key)
    {
        if (*debug)
            cout << "finding value for key: '" << key << "'" << endl;
        bool reading = false;
        bool readingval = false;
        bool readingmeta = false;
        string rkey = "";
        string rval = "";

        for (const char c : data)
        {
            if (c == BEG) reading = true;
            if (c == META)
            {
                readingmeta = true;
                reading = false;
            }
            if (c == VAL && readingmeta)
            {
                readingmeta = false;
                if (*debug)
                    cout << "finished reading key: '" << rkey << "' comparing to '" << key << "'" << endl;
                if (rkey == key) readingval = true;
                rkey = "";
            }
            if ((c == BEG || c == (char)0x00) && readingval) return rval;
            if (reading && c != BEG) rkey += c;
            if (readingval && c != VAL) rval += c;
        }

        if (readingval && !rval.empty())
            return rval;

        return "(nil)";
    }

    bool key_exists(string key)
    {
        bool reading = false;
        string rkey = "";

        for (const char c : data)
        {
            if (c == BEG) reading = true;
            if (c == META && reading)
            {
                reading = false;
                if (*debug)
                    cout << "finished reading key: '" << rkey << "' comparing to '" << key << "'" << endl;
                if (rkey == key) return true;
                rkey = "";
            }
            if (reading && c != BEG) rkey += c;
        }

        return false;
    }

    bool delete_key(string key)
    {
        if (*debug)
            cout << "deleting value for key: '" << key << "'" << endl;

        vector<DBEntry> keys = get_key_data(key);
        int deletedbytes = 0;
        if (keys.empty())
            return false;

        for (DBEntry e : keys)
        {
            if (e.key == key)
            {
                if (*debug)
                {
                    cout << "deleting key: " << e << endl;
                    cout << "starting at " << e.keystart - deletedbytes - 1 << endl;
                }
                data.erase(data.begin() + e.keystart - deletedbytes - 1,
                           data.begin() + e.keystart + e.entry_size() - deletedbytes + 1);
                deletedbytes += e.entry_size() + 2;
            }
        }

        return true;
    }

    string save(string filename)
    {
        ofstream f;
        f.open(filename, ios_base::binary);
        for (const char b : data)
            f.write(&b, 1);
        f.close();
        return "OK";
    }

    KeyType key_type(string key)
    {
        bool reading = false;
        string rkey = "";
        int metaindex = 0;

        for (const char c : data)
        {
            metaindex++;
            if (c == BEG) reading = true;
            if (c == META && reading)
            {
                reading = false;
                if (*debug)
                    cout << "finished reading key: '" << rkey << "' comparing to '" << key << "'" << endl;
                if (rkey == key) goto checkmetadata;
                rkey = "";
            }
            if (reading && c != BEG) rkey += c;
        }

checkmetadata:
        unsigned char buffer[META_SIZE];
        for (int i = 0; i < META_SIZE; i++)
            buffer[i] = data.at(metaindex + i);
        unsigned int a = to_int(buffer);
        cout << a << endl;
        if (a == 0) return KeyValue;
        if (a == 1) return Set;
        return List;
    }

    vector<string> smembers(string setname)
    {
        bool reading = false;
        bool readingmeta = false;
        bool correctmeta = false;
        string rkey = "";
        string sval = "";
        int metaindex = 0;
        vector<string> out;

        for (const char c : data)
        {
            metaindex++;
            if (c == BEG)
            {
                reading = true;
                correctmeta = false;
                readingmeta = false;
            }
            if (c == META && reading)
            {
                readingmeta = true;
                reading = false;
                if (*debug)
                    cout << "finished reading key: '" << rkey << "' comparing to '" << setname << "'" << endl;
                if (rkey == setname)
                {
                    unsigned char buffer[META_SIZE];
                    for (int i = 0; i < META_SIZE; i++)
                        buffer[i] = data.at(metaindex + i);
                    unsigned int a = to_int(buffer);
                    if (a == Set)
                        correctmeta = true;
                }
                rkey = "";
            }
            if (c == VAL && correctmeta)
            {
                // cout << sval << endl;
                readingmeta = false;
                if (!sval.empty())
                    out.push_back(sval);
                sval = "";
            }
            if (reading && c != BEG) rkey += c;
            if (correctmeta && !readingmeta && c != META && c != BEG && c != VAL) sval += c;
        }

        if (!sval.empty())
            out.push_back(sval);
        //out.erase(out.begin());

        return out;
    }

    bool sismember(string setname, string val)
    {
        bool reading = false;
        bool readingmeta = false;
        bool correctmeta = false;
        string rkey = "";
        string sval = "";
        int metaindex = 0;

        for (const char c : data)
        {
            metaindex++;
            if (c == BEG)
            {
                reading = true;
                correctmeta = false;
                readingmeta = false;
            }
            if (c == META && reading)
            {
                readingmeta = true;
                reading = false;
                if (*debug)
                    cout << "finished reading key: '" << rkey << "' comparing to '" << setname << "'" << endl;
                if (rkey == setname)
                {
                    unsigned char buffer[META_SIZE];
                    for (int i = 0; i < META_SIZE; i++)
                        buffer[i] = data.at(metaindex + i);
                    unsigned int a = to_int(buffer);
                    if (a == Set)
                        correctmeta = true;
                }
                rkey = "";
            }
            if (c == VAL && correctmeta)
            {
                // cout << sval << endl;
                readingmeta = false;
                if (sval == val && correctmeta)
                    return true;
                sval = "";
            }
            if (reading && c != BEG) rkey += c;
            if (correctmeta && !readingmeta && c != META && c != BEG && c != VAL) sval += c;
        }

        if (sval == val && correctmeta)
            return true;

        return false;
    }

    bool srem(string setname, string val)
    {
        vector<DBEntry> keys = get_key_data(setname);
        int deletedbytes = 0;
        if (keys.empty())
            return false;

        for (DBEntry e : keys)
        {
            if (e.value == val)
            {
                if (*debug)
                {
                    cout << "deleting key: " << e << endl;
                    cout << "starting at " << e.keystart - deletedbytes - 1 << endl;
                }
                data.erase(data.begin() + e.keystart - deletedbytes - 1,
                           data.begin() + e.keystart + e.entry_size() - deletedbytes + 1);
                deletedbytes += e.entry_size() + 2;
            }
        }

        return true;
    }

    string srandmember(string setname)
    {
        vector<DBEntry> keys = get_key_data(setname);
        if (keys.empty())
            return "(nil)";

        if (*debug)
            cout << "random keys to choose from: " << keys.size() << endl;

        uniform_int_distribution<int> dist(0, keys.size() - 1);
        int randkey = dist(gen);

        if (*debug)
            cout << "chose key number: " << randkey << endl;

        return keys.at(randkey).value;
    }

    string randomkey()
    {
        vector<DBEntry> keys = get_key_data();
        if (keys.empty())
            return "(nil)";

        if (*debug)
            cout << "random keys to choose from: " << keys.size() << endl;

        uniform_int_distribution<int> dist(0, keys.size() - 1);
        int randkey = dist(gen);

        if (*debug)
            cout << "chose key number: " << randkey << endl;

        return keys.at(randkey).key;
    }

    bool smove(string from, string to, string member)
    {
        vector<DBEntry> keys = get_key_data(from);
        if (keys.empty())
            return false;
        vector<DBEntry> destkeys = get_key_data(to);
        if (destkeys.empty() || destkeys.at(0).keytype != 1)
            return false;

        for (const DBEntry e : keys)
            if (e.value == member)
            {
                if (*debug)
                    cout << "member to move found: " << e << endl;
                sadd(to, member);
                srem(from, member);
                return true;
            }

        return false;
    }

    int key_start_index(string key)
    {
        bool reading = false;
        string rkey = "";
        int index = 0;

        for (const char c : data)
        {
            if (c == BEG)
                reading = true;
            if (c == META)
            {
                if (rkey == key)
                    return index - key.length();
                rkey = "";
                reading = false;
            }
            if (reading && c != BEG)
                rkey += c;
            index++;
        }

        return -1;
    }

    map<int, string> key_start_index_multi(string key = "")
    {
        bool reading = false;
        string rkey = "";
        int index = 0;
        map<int, string> out;

        for (const char c : data)
        {
            if (c == BEG)
                reading = true;
            if (c == META)
            {
                if (rkey == key || key == "")
                    out[index - key.length()] = rkey;
                rkey = "";
                reading = false;
            }
            if (reading && c != BEG)
                rkey += c;
            index++;
        }

        return out;
    }

    int keys()
    {
        int out = 0;
        for (const char c : data)
            if (c == BEG)
                out++;
        return out;
    }

    vector<DBEntry> get_key_data(string key = "")
    {
        vector<DBEntry> out;
        map<int, string> startindex = key_start_index_multi(key);
        if (startindex.empty())
            return out;

        for (auto const& x : startindex)
        {
            DBEntry entry;
            entry.key = x.second;
            entry.keystart = x.first;

            unsigned char buffer[META_SIZE];
            for (int i = 0; i < META_SIZE; i++)
                buffer[i] = data.at(x.first + key.length() + i + 1);
            entry.metadata = to_int(buffer);

            if (entry.metadata == 0)
                entry.keytype = KeyValue;
            else if (entry.metadata == 1)
                entry.keytype = Set;
            else
                entry.keytype = List;

            int valstart = x.first + key.length() + META_SIZE + 2;
            string val = "";
            int index = 0;
            while (data.size() != valstart + index &&
                   data.at(valstart + index) != (char)0xee &&
                   data.at(valstart + index) != (char)0x00)
            {
                val += data.at(valstart + index);
                index++;
            }
            entry.value = val;

            out.push_back(entry);
        }

        return out;
    }

    void print_hex(int i)
    {
        cout << hex << setfill('0') << setw(2) << i << " " << endl;
    }

    void print_string_bytes(string s)
    {
        for (char c : s)
            cout << hex << int(c) << " ";
        cout << endl;
    }

    unsigned int to_int(unsigned char bytes[META_SIZE])
    {
        unsigned int a = int((unsigned char)(bytes[0]) << 24 |
                             (unsigned char)(bytes[1]) << 16 |
                             (unsigned char)(bytes[2]) << 8 |
                             (unsigned char)(bytes[3]));
        return a;
    }

    void to_bytes(unsigned int i, unsigned char* arr)
    {
        arr[0] = (i >> 24) & 0xFF;
        arr[1] = (i >> 16) & 0xFF;
        arr[2] = (i >> 8) & 0xFF;
        arr[3] = i & 0xFF;
    }
};
