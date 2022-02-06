#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Parser
{
public:
    bool debug;

    Parser(bool d = false)
    {
        debug = d;
    }

    vector<string> parse(string s)
    {
        if (s.empty()) return {};
        vector<string> out;

        if(debug)
            cout << "parsing: '" << s << "'" << endl;

        // trim spaces at the beginning and end of the string
        while (s.at(0) == ' ')
            s = s.substr(1);
        while (s.at(s.size() - 1) == ' ')
            s = s.substr(0, s.size() - 1);

        if(debug)
            cout << "trimmed: '" << s << "'" << endl;

        stringstream ss (s);
        string item;
        bool readingquote = false;
        string quote = "";

        while (getline (ss, item, ' '))
        {
            if(debug)
                cout << "item: " << item << endl;
            if (item.find("\"") == string::npos && !readingquote)
            {
                if(debug)
                    cout << "does not have quote: " << item << endl;
                out.push_back(item);
            }
            else
            {
                for (char &c : item)
                {
                    if (c == '"' && readingquote == true)
                    {
                        readingquote = false;
                        c = '\'';
                        out.push_back(quote);
                    }
                    if (c == '"' && readingquote == false)
                    {
                        readingquote = true;
                        quote = "";
                    }
                    if (readingquote && c != '"')
                        quote += c;
                }
            }
            quote += " ";
        }

        return out;
    }
};
