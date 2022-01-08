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

class Database
{
public:
    vector<char> data;
    bool* debug;

    Database(bool* d)
    {
        // adds magic value and version
        char magic[7] = "GRAPHY";
        for (int i = 0; i < 6; i++)
            data.push_back(magic[i]);
        data.push_back((char)0x01);

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
        const char* ckey = key.c_str();
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
            cout << "finding value for key: '" << key << "'" << endl;
        const char* ckey = key.c_str();
        int len = strlen(ckey);
        int keystart = 0;
        bool reading = false;
        bool readingval = false;
        string rkey = "";
        int i = 0;

        for (char& c : data)
        {
            if (c == BEG)
            {
                if (!readingval) keystart = i;
                reading = true;
                // readingval = false;
            }
            if (c == META && reading)
            {
                reading = false;
                if (*debug)
                    cout << "finished reading key: '" << rkey << "' comparing to '" << key << "'" << endl;
                if (rkey == key) readingval = true;
                rkey = "";
            }
            if (c == BEG && readingval) goto overwrotekey;
            if (reading && c != BEG && c != META) rkey += c;
            if (readingval) c = 0x00;
            i++;
        }

        if (readingval)
            goto overwrotekey;

        return false;

overwrotekey:
        if (*debug)
            cout << "key starts at: " << keystart << " and is: " << len << " bytes long" << endl;
        // add 5 to account for metadata flag and data
        for (int i = keystart; i <= keystart + len + META_SIZE + 1; i++)
            data.at(i) = 0x00;

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
        bool readingval = false;
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
                readingval = false;
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
                readingval = true;
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
        bool readingval = false;
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
                readingval = false;
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
                readingval = true;
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

    int keys()
    {
        int out = 0;
        for (const char c : data)
            if (c == BEG)
                out++;
        return out;
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