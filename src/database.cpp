#include <iostream>
#include <unordered_map>
#include <string>
#include <string.h>
#include <iomanip>
#include <functional>
#include <vector>
#include <fstream>
#include <assert.h>

using namespace std;

// ----- START -----
// "GRAPHY" - 6 bytes magic value
// 0x01 - 1 byte version number
// ----- KEY VALUE ENTRY -----
// 0xEE - 1 byte beginning code
// x bytes - key
// 0xFF - 1 byte seperation character
// x bytes - value
// ----- REPEAT KEY VALUE ENTRY -----

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
        data.push_back((char)0xEE);

        // add key
        const char* ckey = key.data();
        int len = strlen(ckey);
        for (int i = 0; i < len; i++)
            data.push_back(ckey[i]);

        data.push_back((char)0xFF);

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
        string rkey = "";
        string rval = "";

        for (const char c : data)
        {
            if (c == (char)0xEE) reading = true;
            if (c == (char)0xFF && reading)
            {
                reading = false;
                if (*debug)
                    cout << "finished reading key: '" << rkey << "' comparing to '" << key << "'" << endl;
                if (rkey == key) readingval = true;
                rkey = "";
            }
            if ((c == (char)0xEE || c == (char)0x00) && readingval) return rval;
            if (reading && c != (char)0xEE) rkey += c;
            if (readingval && c != (char)0xFF) rval += c;
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
            if (c == (char)0xEE) reading = true;
            if (c == (char)0xFF && reading)
            {
                reading = false;
                if (*debug)
                    cout << "finished reading key: '" << rkey << "' comparing to '" << key << "'" << endl;
                if (rkey == key) return true;
                rkey = "";
            }
            if (reading && c != (char)0xEE) rkey += c;
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
            if (c == (char)0xEE)
            {
                if (!readingval) keystart = i;
                reading = true;
                // readingval = false;
            }
            if (c == (char)0xFF && reading)
            {
                reading = false;
                if (*debug)
                    cout << "finished reading key: '" << rkey << "' comparing to '" << key << "'" << endl;
                if (rkey == key) readingval = true;
                rkey = "";
            }
            if (c == (char)0xEE && readingval) goto overwrotekey;
            if (reading && c != (char)0xEE && c != (char)0xFF) rkey += c;
            if (readingval) c = 0x00;
            i++;
        }

        if (readingval)
            goto overwrotekey;

        return false;

overwrotekey:
        if (*debug)
            cout << "key starts at: " << keystart << " and is: " << len << " bytes long" << endl;
        for (int i = keystart; i <= keystart + len; i++)
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

    int keys()
    {
        int out = 0;
        for (const char c : data)
            if (c == (char)0xEE)
                out++;
        return out;
    }
};