#include "../graphy.h"

string Graphy::flushdb(Database *db)
{
    db->flushdb();
    return "OK";
}
