#include "database.h"

void Database::sadd(string setname, string value)
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

vector<string> Database::smembers(string setname)
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

bool Database::sismember(string setname, string val)
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

bool Database::srem(string setname, string val)
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

string Database::srandmember(string setname)
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

bool Database::smove(string from, string to, string member)
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
