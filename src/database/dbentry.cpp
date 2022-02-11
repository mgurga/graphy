#include "database.h"

DBEntry::DBEntry() {}

DBEntry::DBEntry(string key, string val, uint meta)
{
    this->key = key;
    this->value = val;
    this->metadata = meta;
}

bool operator== (DBEntry const& a, const DBEntry& b)
{
    return (a.key == b.key && a.metadata == b.metadata && a.value == b.value);
}

ostream& operator<< (ostream &out, DBEntry const& data)
{
    out << "key: '" << data.key << "' metadata: " << data.metadata << " value: '" << data.value << "' key start index: " << data.keystart;
    return out;
}

int DBEntry::entry_size()
{
    return key.length() + META_SIZE + value.length() + 1;
}
