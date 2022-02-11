#include "database.h"

ostream& operator<< (ostream &out, DBEntry const& data)
{
    out << "key: '" << data.key << "' metadata: " << data.metadata << " value: '" << data.value << "' key start index: " << data.keystart;
    return out;
}

int DBEntry::entry_size()
{
    return key.length() + META_SIZE + value.length() + 1;
}
