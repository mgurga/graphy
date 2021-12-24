#include <iostream>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <functional>

using namespace std;

// IM GOING TO REWRITE THIS!!! THIS CODE IS ONLY FOR A PROOF OF CONCEPT!!!
class Database
{
public:
    unordered_map<int, string> data;

    Database() {}

    void set(string key, string value)
    {
        data[hash<string>{}(key)] = value;
    }

    string get(string key)
    {
        return data.at(hash<string>{}(key));
    }
};