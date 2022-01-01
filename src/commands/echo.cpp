#include <string>
#include <ctime>

#ifndef PARSER_CPP
#define PARSER_CPP
#include "../parser.cpp"
#endif

inline string echo(string s)
{
    Parser p;
    vector<string> args = p.parse(s);
    if (args.size() == 0 || args.size() > 1) return "ERR incorrect number of arguments";
    return args.at(0);
}