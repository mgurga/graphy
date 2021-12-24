#include "graphy.cpp"
#include "UnitTest++/UnitTest++.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "test") == 0)
        return UnitTest::RunAllTests();
    else if (argc > 2 && strcmp(argv[1], "r") == 0)
    {
        // run singular command
        string cmd = "";
        for (int i = 2; i < argc; i++)
        {
            cmd.append(argv[i]);
            cmd.append(" ");
        }

        Graphy g;
        // cout << "sending command: " << cmd << endl;
        cout << g.command(cmd) << endl;
        return 1;
    }
    else if (argc == 1)
    {
        // interactive shell
        cout << "graphy interactive shell" << endl;
        bool open = true;
        Graphy g;
        while(open)
        {
            cout << ">> ";
            string input;
            getline(cin, input);
            if(input == "d")
                g.debug = !g.debug;
            else
                cout << g.command(input) << endl;
        }
    } else
        cout << "unknown command" << endl;

    return 1;
}