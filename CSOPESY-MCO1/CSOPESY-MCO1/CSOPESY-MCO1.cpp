#include <iostream>
#include <fstream>
#include <cstdlib>
#include "header.h"
#include "ConsoleManager.h"
#include "NvidiaSmi.h"
#include "FCFS.h"
#include <vector>
#include <iomanip> // For put_time
#include <sstream> // For ostringstream

using namespace std;
vector<ProcessInfo> processes;

int main() {
    ConsoleManager consoleManager;
    header();
    bool running = true;
    bool initialized = false;

    int num_cpu;                // Number of CPUs
    string sched;               // Scheduler type (fcfs or rr)
    int quant_cycles;           // Quantum cycles range: 1 to 2^32
    int batch_process_freq;     // Batch process frequency range: 1 to 2^32
    int max_ins;                // Max instructions range: 1 to 2^32 
    int min_ins;                // Min instructions range: 1 to 2^32 
    int delay_per_exec;         // Delay per execution range: 0 to 2^32

    FCFS_Scheduler scheduler(4, 10, &consoleManager);  // 4 CPU cores, 10 processes

    while (running) {
        cout << "command: ";
        string user_input;
        getline(cin, user_input);

        if (user_input == "initialize") {
            cout << "executing initialize...\n";
            initialized = true;

            // Insert file reading here for the config.txt
            ifstream configFile("config.txt");
            if (configFile.is_open()) {
                string key;
                while (configFile >> key) {
                    if (key == "num_cpu") {
                        configFile >> num_cpu;
                    }
                    else if (key == "scheduler") {
                        configFile >> sched;
                    }
                    else if (key == "quantum_cycles") {
                        configFile >> quant_cycles;
                    }
                    else if (key == "batch_process_freq") {
                        configFile >> batch_process_freq;
                    }
                    else if (key == "min_ins") {
                        configFile >> min_ins;
                    }
                    else if (key == "max_ins") {
                        configFile >> max_ins;
                    }
                    else if (key == "delay_per_exec") {
                        configFile >> delay_per_exec;
                    }
                    else {
                        cout << "Unknown configuration key: " << key << "\n";
                    }
                }
                configFile.close();
                cout << "Configuration loaded successfully.\n";
                cout << "=====================================\n";
                cout << "Number of CPUs: " << num_cpu << "\n";
                cout << "Scheduler type: " << sched << "\n";
                cout << "Quantum cycles: " << quant_cycles << "\n";
                cout << "Batch process frequency: " << batch_process_freq << "\n";
                cout << "Minimum instructions: " << min_ins << "\n";
                cout << "Maximum instructions: " << max_ins << "\n";
                cout << "Delay per execution: " << delay_per_exec << "\n";
                cout << "=====================================\n";
            }
            else {
                cout << "Unable to open config.txt\n";
                initialized = false;
            }

            while (initialized) {
                cout << "command: ";
                getline(cin, user_input);
                if (user_input.substr(0, 6) == "screen") {
                    string command = user_input.substr(7);
                    stringstream ss(command);
                    string action, name;
                    ss >> action >> name;

                    if (action == "-s") {
                        // Get the current time
                        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
                        // Thread-safe local time conversion
                        struct tm local_time;
                        localtime_s(&local_time, &now); // Use localtime_s for safety
                        // Create a formatted timestamp (MM/DD/YYYY, HH:MM:SS AM/PM)
                        ostringstream oss;
                        oss << put_time(&local_time, "%m/%d/%Y, %I:%M:%S %p");
                        string timestamp = oss.str();

                        consoleManager.addProcess(name, "Running", 1, timestamp, 0);
                    }
                    else if (action == "-r") {
                        system("cls");
                        header();
                        consoleManager.displayProcess(name);
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
                else if (user_input == "clear" || user_input == "cls") {
                    system("cls");
                    header();
                }
                else if (user_input == "exit") {
                    initialized = false;
                    system("cls");
                    header();
                    break;
                }
                else {
                    cout << "Invalid Command\n";
                }
            }
        }
        else {
            cout << "Invalid Command\n";
        }
    }
}
