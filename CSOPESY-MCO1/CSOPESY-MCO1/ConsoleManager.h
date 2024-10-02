#pragma once
// ConsoleManager.h
#ifndef CONSOLE_MANAGER_H
#define CONSOLE_MANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>

class Screen {
public:
    std::string name;
    std::string process_name;
    int current_line;
    int total_lines;
    std::string timestamp;

    Screen(const std::string& name, const std::string& process_name, int current_line, int total_lines);
    void display() const;
};

class ConsoleManager {
private:
    std::vector<Screen> screens;

public:
    void createScreen(const std::string& name, const std::string& process_name, int total_lines);
    void displayScreen(const std::string& name);
    void removeScreen(const std::string& name);
};

#endif // CONSOLE_MANAGER_H

