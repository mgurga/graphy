#include "database.h"

using namespace std;

void Database::set(string key, string value)
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

string Database::get(string key)
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

bool Database::key_exists(string key)
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

bool Database::delete_key(string key)
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

KeyType Database::key_type(string key)
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

string Database::randomkey()
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

int Database::key_start_index(string key)
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

map<int, string> Database::key_start_index_multi(string key)
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

int Database::keys()
{
    int out = 0;
    for (const char c : data)
        if (c == BEG)
            out++;
    return out;
}

vector<DBEntry> Database::get_key_data(string key)
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

void Database::add_dbentry(DBEntry dbe)
{
    if (*debug)
        cout << "key: '" << dbe.key << "' to value: '" << dbe.value << "'" << endl;
    // beginning byte
    data.push_back(BEG);

    // add key
    const char* ckey = dbe.key.data();
    int len = strlen(ckey);
    for (int i = 0; i < len; i++)
        data.push_back(ckey[i]);

    data.push_back(META);

    // add metadata
    unsigned char bytes[META_SIZE];
    to_bytes(dbe.metadata, bytes);
    for (int i = 0; i < META_SIZE; i++)
        data.push_back(bytes[i]);

    data.push_back(VAL);

    // add value
    const char* cval = dbe.value.data();
    len = strlen(cval);
    for (int i = 0; i < len; i++)
        data.push_back(cval[i]);
}

bool Database::delete_dbentry(DBEntry dbe)
{
    vector<DBEntry> keys = get_key_data(dbe.key);
    int deletedbytes = 0;
    if (keys.empty())
        return false;

    for (DBEntry e : keys)
    {
        if (e == dbe)
        {
            if (*debug)
            {
                cout << "deleting key: " << e << endl;
                cout << "starting at " << e.keystart - deletedbytes - 1 << endl;
            }
            data.erase(data.begin() + e.keystart - deletedbytes - 1,
                       data.begin() + e.keystart + e.entry_size() - deletedbytes + 1);
            deletedbytes += e.entry_size() + 2;
            return true;
        }
    }

    return false;
}
