#include <iostream>
#include <cstdlib>
#include "header.h"
#include "ConsoleManager.h"

using namespace std;

int main()
{
    ConsoleManager consoleManager;
    header();
    bool running = true;

    while (running)
    {
        cout << "command: ";
        string user_input;
        getline(cin, user_input);

        if (user_input == "initialize")
        {
            cout << "executing initialize\n";
        }
        else if (user_input.substr(0, 6) == "screen")
        {
            string command = user_input.substr(7);
            stringstream ss(command);
            string action, name;
            ss >> action >> name;

            if (action == "-r") {
                consoleManager.createScreen(name, "Process-" + name, 10);  // Create a new session
            }
            else if (action == "-s") {
                system("cls");
                consoleManager.displayScreen(name);  // Resume an existing session
                while (1)
                {
                    cout << "command:";
                    getline(cin, user_input);
                    if (user_input == "exit")
                    {
                        system("cls");
                        header();
                        break;
                    }

                }
            }
            else if (action == "-ls") {
                //consoleManager.listSessions();  // List all sessions
                cout << "to be implemented lmao\n";
            }
            else {
                cout << "Invalid screen option\n";
            }
        }
        else if (user_input == "scheduler-test")
        {

            cout << "executing scheduler-test\n";
        }
        else if (user_input == "scheduler-stop")
        {

            cout << "executing scheduler-stop\n";
        }
        else if (user_input == "report-util")
        {

            cout << "executing report-util\n";
        }
        else if (user_input == "clear")
        {
            system("cls");
            header();
        }
        else if (user_input == "exit")
        {
            cout << "exiting\n";
            return 0;
        }
        else
        {
            cout << "Invalid Command\n";
        }
    }
}