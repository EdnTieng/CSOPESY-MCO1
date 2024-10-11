#include "NvidiaSmi.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Display the GPU summary in a similar layout to nvidia-smi
void NvidiaSmi::displayGPUSummary() {
    system("cls");
    cout << "+-----------------------------------------------------------------------------+\n";
    cout << "| EDN-SMI 460.32       Driver Version: 460.32       CUDA Version: 11.2         |\n";
    cout << "|-------------------------------+----------------------+-----------------------|\n";
    cout << "| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC  |\n";
    cout << "| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M.  |\n";
    cout << "|                               |                      |               MIG M.  |\n";
    cout << "|===============================+======================+=======================|\n";
    cout << "|   0  Dummy GPU           On   | 00000000:01:00.0  On |                  N/A  |\n";
    cout << "| N/A   45C    P0    70W / 250W |  200MiB / 8192MiB    |     30%      Default  |\n";
    cout << "+-------------------------------+----------------------+-----------------------+\n";
}

// Display a list of dummy processes
void NvidiaSmi::displayProcesses(const vector<test>& processes) {
    cout << "| Processes:                                                       GPU Memory |\n";
    cout << "|  GPU       PID   Type   Process name                            Usage       |\n";
    cout << "|=============================================================================|\n";
    for (const auto& process : processes) {
        cout << "|    0    " << setw(5) << process.pid << "   " << setw(3) << process.type << "   "
            << setw(40) << left << truncateProcessName(process.processName, 37) << "   " << process.gpuMemUsage << " |\n";
    }
    cout << "+-----------------------------------------------------------------------------+\n";
}

// Utility function to truncate long process names
string NvidiaSmi::truncateProcessName(const string& name, size_t maxLength) {
    if (name.length() > maxLength) {
        return name.substr(0, maxLength - 3) + "...";  // Truncate and add ellipsis
    }
    return name;
}
