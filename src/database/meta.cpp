#include "database.h"

Database::Database(bool* d)
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

void Database::flushdb()
{
    data.erase(data.begin() + 7, data.end());
}

string Database::save(string filename)
{
    ofstream f;
    f.open(filename, ios_base::binary);
    for (const char b : data)
        f.write(&b, 1);
    f.close();
    return "OK";
}
