#include "FCFS.h"
#include <iomanip> // For put_time
#include <sstream> // For ostringstream
#include <random>  // For random number generation

using namespace std;

FCFS_Scheduler::FCFS_Scheduler(int coreCount, int min_ins, int max_ins, ConsoleManager* consoleManager)
    : coreCount(coreCount), min_ins(min_ins), max_ins(max_ins), running(false), consoleManager(consoleManager) {}

void FCFS_Scheduler::start() {
    running = true;

    // Start the scheduler thread
    schedulerThread = thread(&FCFS_Scheduler::schedulerFunction, this);

    // Start the CPU worker threads
    for (int i = 0; i < coreCount; i++) {
        cpuWorkers.emplace_back(&FCFS_Scheduler::cpuWorker, this, i);
    }
}

void FCFS_Scheduler::schedulingTestStart(bool run) {
    if (run) {
        schedulingTestThread = std::thread([this]() {
            int processId = 0;
            while (running) {
                // Create and enqueue a new process
                processQueue.push(new Process(processId++));

                // Notify worker threads about the new process
                cv.notify_all();

                // Delay between process creations, adjust as needed
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            });
    }
    else {
        if (schedulingTestThread.joinable()) {
            schedulingTestThread.join();  // Stop and clean up the thread
        }
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
    // Set up random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min_ins, max_ins);

    while (running) {
        Process* process = nullptr;

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (!processQueue.empty()) {
                process = processQueue.front();
                processQueue.pop();

                int random_instructions = dist(gen); // Generate instructions
                process->total_ins = random_instructions;

                // Timestamp generation for the new process
                auto now = std::time(nullptr);
                struct tm local_time;
                localtime_s(&local_time, &now);
                std::ostringstream oss;
                oss << std::put_time(&local_time, "%m/%d/%Y %I:%M:%S %p");
                std::string timestamp = oss.str();

                // Add the new process with instructions to ConsoleManager
                consoleManager->addProcess("Process_" + std::to_string(process->id), "Running", coreId, timestamp, 0, random_instructions);
            } else {
                cv.wait(lock);
            }
        }

        if (process) {
            for (int i = 0; i < process->total_ins; ++i) {
                std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate execution time based on instructions
                consoleManager->updateProcessStatus("Process_" + std::to_string(process->id), "Running", i + 1);
            }

            consoleManager->updateProcessStatus("Process_" + std::to_string(process->id), "Finished", process->total_ins);
            delete process;
        }
    }
}



