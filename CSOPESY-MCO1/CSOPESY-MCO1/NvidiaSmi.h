#pragma once
#ifndef NVIDIA_SMI_H
#define NVIDIA_SMI_H

#include <string>
#include <vector>

struct Process {
    int pid;
    std::string type;
    std::string processName;
    std::string gpuMemUsage;
};

class NvidiaSmi {
public:
    // Function to display GPU summary
    void displayGPUSummary();

    // Function to display processes
    void displayProcesses(const std::vector<Process>& processes);

    // Utility function to truncate long process names
    std::string truncateProcessName(const std::string& name, size_t maxLength);

    // Add more methods as needed for managing the console layout
};

#endif


