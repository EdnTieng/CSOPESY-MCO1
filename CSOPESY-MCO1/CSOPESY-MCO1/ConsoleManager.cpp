#include "ConsoleManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <fstream>  

using namespace std;

// Adds a new process to the ConsoleManager with its initial status, core ID, timestamp, and progress
void ConsoleManager::addProcess(const std::string& name, const std::string& status, int coreId, const std::string& timestamp, int progress, int num_ins) {
    for (auto& process : processes) {
        if (process.name == name) {
            // If the process already exists, just update its fields
            process.status = status;
            process.coreId = coreId;
            process.timestamp = timestamp;
            process.progress = progress;
            process.num_ins = num_ins; // Might be useful to update if it changes
            return; // Exit once the process is found and updated
        }
    }
    // If it doesn't exist, create a new one
    processes.push_back({ name, status, coreId, timestamp, progress, num_ins });
}


// Displays details of a specific process
void ConsoleManager::displayProcess(const std::string& process_name) const {
    for (const auto& process : processes) {
        if (process.name == process_name) {
            cout << "Process Name: " << process.name << "\n";
            cout << "Status: " << process.status << "\n";
            cout << "Core ID: " << process.coreId << "\n";
            cout << "Timestamp: " << process.timestamp << "\n";
            cout << "Progress: " << process.progress << "/"<< process.num_ins << "\n";
            return;
        }
    }
    cout << "Process \"" << process_name << "\" not found.\n";
}

// Removes a process from the list based on its name
void ConsoleManager::removeProcess(const std::string& process_name) {
    processes.erase(remove_if(processes.begin(), processes.end(),
        [&process_name](const ProcessInfo& process) {
            return process.name == process_name;
        }), processes.end());
}

// Updates the status and progress of a process
void ConsoleManager::updateProcessStatus(const std::string& process_name, const std::string& status, int progress) {
    for (auto& process : processes) {
        if (process.name == process_name) {
            process.status = status;
            process.progress = progress;
            return;
        }
    }
}

// Lists all processes, displaying both "Running" and "Finished" processes separately
void ConsoleManager::listProcesses() const {
    system("cls");
    cout << "------------------------------------\n";
    cout << "Running processes:\n";
    for (const auto& process : processes) {
        if (process.status == "Running") {
            cout << process.name << "\t" << "\t(" << process.timestamp << ")\tCore:\t" << process.coreId
                << "\tProgress: " << process.progress << "/" << process.num_ins << "\n";
        }
    }
    cout << "\nFinished processes:\n";
    for (const auto& process : processes) {
        if (process.status == "Finished") {
            cout << process.name << "\t(" << process.timestamp << ")\tFinished \tProgress: " << process.progress << "/" << process.num_ins << "\n";
        }
    }
    cout << "------------------------------------\n";
}
void ConsoleManager::printProcesses() const {
    std::ofstream outFile("csopesy-log.txt");  // Open the file in write mode

    if (!outFile) {
        std::cerr << "Error: Could not open csopesy-log.txt for writing." << std::endl;
        return;
    }

    outFile << "------------------------------------\n";
    outFile << "Running processes:\n";
    for (const auto& process : processes) {
        if (process.status == "Running") {
            outFile << process.name << "\t" << "\t(" << process.timestamp << ")\tCore:\t" << process.coreId
                << "\tProgress: " << process.progress << "/" << process.num_ins << "\n";
        }
    }

    outFile << "\nFinished processes:\n";
    for (const auto& process : processes) {
        if (process.status == "Finished") {
            outFile << process.name << "\t(" << process.timestamp << ")\tFinished \tProgress: " << process.progress << "/" << process.num_ins << "\n";
        }
    }

    outFile << "------------------------------------\n";
    outFile.close();  // Close the file

    std::cout << "Process log has been written to csopesy-log.txt." << std::endl;
}