#include <iostream>
#include <cstdlib>
#include "header.h"
#include "ConsoleManager.h"
#include "NvidiaSmi.h"
#include "FCFS.h"
#include <vector>

using namespace std;
vector<ProcessInfo> processes;

int main() {
    //NvidiaSmi nvidiaSmi;
    ConsoleManager consoleManager;
    header();
    bool running = true;
    bool initialized = false;
    FCFS_Scheduler scheduler(4, 10, &consoleManager);  // 4 CPU cores, 10 processes

    while (running) {
        cout << "command: ";
        string user_input;
        getline(cin, user_input);

        if (user_input == "initialize") {
            cout << "executing initialize\n";
            initialized = true;
            while (initialized) {
                cout << "command: ";
                getline(cin, user_input);
                if (user_input.substr(0, 6) == "screen") {
                    string command = user_input.substr(7);
                    stringstream ss(command);
                    string action, name;
                    ss >> action >> name;

                    if (action == "-r") {
                        consoleManager.createScreen(name, "Process-" + name, 10);
                    }
                    else if (action == "-s") {
                        system("cls");
                        consoleManager.displayScreen(name);
                    }
                    else if (action == "-ls") {
                        consoleManager.listProcesses(); // Display all processes
                    }
                    else {
                        cout << "Invalid screen option\n";
                    }
                }
                else if (user_input == "scheduler-test") {
                    cout << "Starting FCFS scheduler...\n";
                    scheduler.start();
                }
                else if (user_input == "scheduler-stop") {
                    cout << "Stopping FCFS scheduler...\n";
                    scheduler.stop();
                }
                else if (user_input == "report-util") {
                    cout << "executing report-util\n";
                }
                else if (user_input == "clear") {
                    system("cls");
                    header();
                }
                else if (user_input == "exit") {
                    cout << "exiting\n";
                    return 0;
                }
                else {
                    cout << "Invalid Command\n";
                }
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
        else if (user_input == "exit") {
            cout << "exiting\n";
            return 0;
        }
        else {
            cout << "Invalid Command\n";
        }
    }
}
