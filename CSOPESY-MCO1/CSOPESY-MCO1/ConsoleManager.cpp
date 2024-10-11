#include "ConsoleManager.h"
#include <iostream>
#include <cstdlib>
#include "header.h"
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;
// Screen constructor
Screen::Screen(const std::string& name, const std::string& process_name, int current_line, int total_lines)
    : name(name), process_name(process_name), current_line(current_line), total_lines(total_lines) {
    // Set timestamp in MM/DD/YYYY, HH:MM:SS AM/PM format
    auto now = std::time(nullptr);
    struct tm local_time;
    localtime_s(&local_time, &now); // Use localtime_s for thread-safe local time

    std::ostringstream oss;
    oss << std::put_time(&local_time, "%m/%d/%Y, %I:%M:%S %p");
    timestamp = oss.str();
}

// Display screen information
void Screen::display() const {
    std::cout << "Screen: " << name << "\n";
    std::cout << "Process Name: " << process_name << "\n";
    std::cout << "Current Line: " << current_line << " / Total Line: " << total_lines << "\n";
    std::cout << "Timestamp: " << timestamp << "\n";
}

// Create a new screen
void ConsoleManager::createScreen(const std::string& name, const std::string& process_name, int total_lines) {
    screens.emplace_back(name, process_name, 1, total_lines);
    std::cout << "Screen \"" << name << "\" created.\n";
}

// Display a specific screen
void ConsoleManager::displayScreen(const std::string& name) {
    for (const auto& screen : screens) {
        if (screen.name == name) {
            string user_input;
            screen.display();
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
                else
                {
                    cout << "Invalid Command\n";
                }
            }
            return;
        }
    }
    std::cout << "Screen \"" << name << "\" not found.\n";
}

// Remove a screen by name
void ConsoleManager::removeScreen(const std::string& name) {
    screens.erase(std::remove_if(screens.begin(), screens.end(), [&name](const Screen& screen) {
        return screen.name == name;
        }), screens.end());
}

void ConsoleManager::addProcess(const std::string& process_name, const std::string& status, int coreId, const std::string& timestamp, int progress) {
    ProcessInfo info;
    info.name = process_name;
    info.status = status;
    info.coreId = coreId;
    info.timestamp = timestamp;
    info.progress = progress;
    processes.push_back(info);
}

void ConsoleManager::updateProcessStatus(const std::string& process_name, const std::string& status, int progress) {
    for (auto& process : processes) {
        if (process.name == process_name) {
            process.status = status;
            process.progress = progress;
            return;
        }
    }
}

void ConsoleManager::listProcesses() {
    system("cls");
    header();
    cout << "------------------------------------\n";
    cout << "Running processes:\n";
    for (const auto& process : processes) {
        if (process.status == "Running") {
            cout << process.name << "\t(" << process.timestamp << ")\tCore: " << process.coreId
                << "\tProgress: " << process.progress << "/100\n";
        }
    }
    cout << "\nFinished processes:\n";
    for (const auto& process : processes) {
        if (process.status == "Finished") {
            cout << process.name << "\t(" << process.timestamp << ")\tFinished \tProgress: " << process.progress << "/100\n";
        }
    }
    cout << "------------------------------------\n";
}



