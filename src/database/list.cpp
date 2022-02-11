#include "database.h"

int Database::lpush(string list, string val)
{
    vector<DBEntry> listitems = get_key_data(list);
    if (listitems.empty())
    {
        add_dbentry(DBEntry(list, val, 2));
        return 1;
    }

    add_dbentry(DBEntry(list, val, 2));
    for (DBEntry e : listitems)
    {
        delete_dbentry(e);
        add_dbentry(DBEntry(e.key, e.value, e.metadata + 1));
    }

    return listitems.size() + 1;
}

int Database::rpush(string list, string val)
{
    vector<DBEntry> listitems = get_key_data(list);
    if (listitems.empty())
    {
        add_dbentry(DBEntry(list, val, 2));
        return 1;
    }

    int lastsize = 0;
    for (DBEntry e : listitems)
        if (e.metadata > lastsize)
            lastsize = e.metadata;

    add_dbentry(DBEntry(list, val, lastsize + 1));

    return listitems.size() + 1;
}

vector<string> Database::lrange(string list, int start, int stop)
{
    vector<DBEntry> listitems = get_key_data(list);
    vector<string> out;
    if (listitems.empty())
        return out;

    for (int i = start; i < stop; i++)
        for (DBEntry e : listitems)
            if (e.metadata - 2 == i)
                out.push_back(e.value);

    return out;
}
