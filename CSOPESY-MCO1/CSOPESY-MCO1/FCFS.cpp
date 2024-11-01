#include "FCFS.h"
#include <iomanip> // For put_time
#include <sstream> // For ostringstream

using namespace std;

FCFS_Scheduler::FCFS_Scheduler(int coreCount, int processCount, ConsoleManager* consoleManager)
    : coreCount(coreCount), processCount(processCount), running(false), consoleManager(consoleManager) {}

void FCFS_Scheduler::start() {
    running = true;

    // Create 10 processes and add to the queue
    for (int i = 0; i <= processCount; i++) {
        processQueue.push(new Process(i));
    }

    // Start the scheduler thread
    schedulerThread = thread(&FCFS_Scheduler::schedulerFunction, this);

    // Start the CPU worker threads
    for (int i = 0; i < coreCount; i++) {
        cpuWorkers.emplace_back(&FCFS_Scheduler::cpuWorker, this, i);
    }
}

void FCFS_Scheduler::stop() {
    running = false;

    // Notify all workers
    cv.notify_all();

    // Join the scheduler and worker threads
    if (schedulerThread.joinable()) schedulerThread.join();
    for (auto& worker : cpuWorkers) {
        if (worker.joinable()) worker.join();
    }
}

void FCFS_Scheduler::schedulerFunction() {
    while (running) {
        unique_lock<mutex> lock(queueMutex);
        if (!processQueue.empty()) {
            // Notify workers when there are processes
            cv.notify_all();
        }
        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(100)); // Adjust timing if needed
    }
}

void FCFS_Scheduler::cpuWorker(int coreId) {
    while (running) {
        Process* process = nullptr;

        {
            unique_lock<mutex> lock(queueMutex);
            if (!processQueue.empty()) {
                process = processQueue.front();
                processQueue.pop();

                // Get the current time for timestamp
                auto now = std::time(nullptr);
                struct tm local_time;
                localtime_s(&local_time, &now);
                std::ostringstream oss;
                oss << std::put_time(&local_time, "%m/%d/%Y %I:%M:%S %p");
                std::string timestamp = oss.str();

                // Notify ConsoleManager about process creation
                consoleManager->addProcess("Process_" + std::to_string(process->id), "Running", coreId, timestamp, 0);
            }
            else {
                cv.wait(lock);
            }
        }

        if (process) {
            // Execute 100 print commands for each process
            for (int i = 0; i < 100; i++) {
                
                this_thread::sleep_for(chrono::milliseconds(50)); // Simulate execution time

                // Update ConsoleManager with progress
                consoleManager->updateProcessStatus("Process_" + std::to_string(process->id), "Running", i + 1);
            }

            // Mark the process as finished
            consoleManager->updateProcessStatus("Process_" + std::to_string(process->id), "Finished", 100);

            delete process; // Clean up the process
        }
    }
}


