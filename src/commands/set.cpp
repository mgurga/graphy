#include <string>

#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "../database.cpp"
#endif

using namespace std;

inline string set(string s, Database* db, bool debug = false) {
    if (s.empty()) return "ERR";
    int split = s.find(" ", 1);
    if (debug)
        cout << "setting '" << s.substr(1, split) << "' to '" << s.substr(split + 1) << "'" << endl;
    db->set(s.substr(0, split), s.substr(split + 1));
    return "OK";
}