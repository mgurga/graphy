#include "database.h"
#include <algorithm>

int Database::lpush(string list, string val)
{
    vector<DBEntry> listitems = get_key_data(list, List);
    if (listitems.empty())
    {
        add_dbentry(DBEntry(list, val, 2));
        return 1;
    }

    add_dbentry(DBEntry(list, val, 2));
    for (DBEntry &e : listitems)
    {
        delete_dbentry(e);
        add_dbentry(DBEntry(e.key, e.value, e.metadata + 1));
    }

    return listitems.size() + 1;
}

int Database::rpush(string list, string val)
{
    vector<DBEntry> listitems = get_key_data(list, List);
    if (listitems.empty())
    {
        add_dbentry(DBEntry(list, val, 2));
        return 1;
    }

    int lastsize = 0;
    for (DBEntry &e : listitems)
        if (e.metadata > lastsize)
            lastsize = e.metadata;

    add_dbentry(DBEntry(list, val, lastsize + 1));

    return listitems.size() + 1;
}

vector<string> Database::lrange(string list, int start, int stop)
{
    vector<DBEntry> listitems = get_key_data(list, List);
    vector<string> out;
    if (listitems.empty())
        return out;

    if (start < 0)
        start = listitems.size() + start;
    if (stop < 0)
        stop = listitems.size() + stop;

    for (int i = start; i <= stop; i++)
        for (DBEntry &e : listitems)
            if (e.metadata - 2 == i)
                out.push_back(e.value);

    return out;
}

int Database::llen(string key)
{
    vector<DBEntry> listitems = get_key_data(key, List);
    return listitems.size();
}

int Database::lrem(string key, int count, string element)
{
    vector<DBEntry> listitems = sort_list(get_key_data(key, List));
    vector<DBEntry> out;
    if (listitems.empty())
        return 0;

    if (count < 0)
    {
        for (int i = listitems.size() - 1; i >= 0; i--)
            if (listitems.at(i).value == element && count != 0)
                count++;
            else if (listitems.at(i).value != element)
                out.push_back(listitems.at(i));
            else if (count == 0)
                out.push_back(listitems.at(i));
        reverse(out.begin(), out.end());
    }
    else if (count > 0)
    {
        for (int i = 0; i <= listitems.size() - 1; i++)
            if (listitems.at(i).value == element && count != 0)
                count--;
            else if (listitems.at(i).value != element)
                out.push_back(listitems.at(i));
            else if (count == 0)
                out.push_back(listitems.at(i));
    }
    else
        for (int i = 0; i < listitems.size() - 1; i++)
            if (listitems.at(i).value != element)
                out.push_back(listitems.at(i));

    for (DBEntry &e : listitems)
        delete_dbentry(e);
    for (int i = 0; i < out.size(); i++)
    {
        DBEntry e = out.at(i);
        e.metadata = i + 2;
        add_dbentry(e);
    }

    return listitems.size() - out.size();
}

vector<DBEntry> Database::sort_list(vector<DBEntry> e)
{
    vector<DBEntry> out;
    for (int i = 0; i < e.size(); i++)
        for (DBEntry &a : e)
            if (a.metadata == i + 2)
                out.push_back(a);
    return out;
}
