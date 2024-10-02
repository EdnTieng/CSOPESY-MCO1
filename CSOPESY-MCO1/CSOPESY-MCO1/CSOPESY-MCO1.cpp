#include <iostream>
#include <cstdlib>
#include "header.h"

using namespace std;

int main()
{
    bool running = true;
    header();
    while (running)
    {
        cout << "command: ";
        string user_input;
        cin >> user_input;

        if (user_input == "initialize")
        {
            cout << "executing initialize\n";
        }
        else if (user_input == "screen")
        {
            cout << "executing screen";
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