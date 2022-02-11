#include "database.h"

void Database::print_hex(int i)
{
    cout << hex << setfill('0') << setw(2) << i << " " << endl;
}

void Database::print_string_bytes(string s)
{
    for (char c : s)
        cout << hex << int(c) << " ";
    cout << endl;
}

unsigned int Database::to_int(unsigned char bytes[META_SIZE])
{
    unsigned int a = int((unsigned char)(bytes[0]) << 24 |
                         (unsigned char)(bytes[1]) << 16 |
                         (unsigned char)(bytes[2]) << 8 |
                         (unsigned char)(bytes[3]));
    return a;
}

void Database::to_bytes(unsigned int i, unsigned char* arr)
{
    arr[0] = (i >> 24) & 0xFF;
    arr[1] = (i >> 16) & 0xFF;
    arr[2] = (i >> 8) & 0xFF;
    arr[3] = i & 0xFF;
}
