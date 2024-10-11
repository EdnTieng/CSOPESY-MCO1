#pragma once
// ConsoleManager.h
#ifndef CONSOLE_MANAGER_H
#define CONSOLE_MANAGER_H

#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <algorithm>

// Process info struct
struct ProcessInfo {
    std::string name;
    std::string status; // "Running" or "Finished"
    int coreId;
    std::string timestamp;
    int progress; // Out of 100 (e.g., 1235/5876)
};

// Screen class
class Screen {
public:
    Screen(const std::string& name, const std::string& process_name, int current_line, int total_lines);
    void display() const;

    std::string name;
    std::string process_name;
    int current_line;
    int total_lines;
    std::string timestamp;
};

// Console Manager class
class ConsoleManager {
public:
    void createScreen(const std::string& name, const std::string& process_name, int total_lines);
    void displayScreen(const std::string& name);
    void removeScreen(const std::string& name);
    void listSessions(const std::vector<ProcessInfo>& processes); // New function to list session


    void addProcess(const std::string& process_name, const std::string& status, int coreId, const std::string& timestamp, int progress);
    void updateProcessStatus(const std::string& process_name, const std::string& status, int progress);
    void listProcesses();

private:
    std::vector<Screen> screens;

    std::vector<ProcessInfo> processes; // Keep track of process information
};

#endif // CONSOLE_MANAGER_H

