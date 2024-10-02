// ConsoleManager.cpp
#include "ConsoleManager.h"

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
            screen.display();
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
