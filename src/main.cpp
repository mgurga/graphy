#include "graphy.cpp"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc > 2 && (strcmp(argv[1], "r") == 0 || strcmp(argv[1], "rd") == 0))
    {
        // run singular command
        string cmd = "";
        for (int i = 2; i < argc; i++)
        {
            cmd.append(argv[i]);
            cmd.append(" ");
        }
        cmd = cmd.substr(0, cmd.length() - 1);

        Graphy g;
        // cout << "sending command: " << cmd << endl;
        if (strcmp(argv[1], "rd") == 0)
            g.debug = true;
        cout << g.command(cmd) << endl;
        return 0;
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
            else if(input == "quit")
            {
                cout << g.command(input) << endl;
                exit(0);
            }
            else
                cout << g.command(input) << endl;
        }
    } else
        cout << "unknown command" << endl;

    return 0;
}
