#pragma once
#ifndef FCFS_H
#define FCFS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <string>
#include "consoleManager.h"

using namespace std;

class Process {
public:
    int id;
    int printCount;
    string filename;

    Process(int pid) : id(pid), printCount(0) {
        filename = "process_" + to_string(id) + ".txt";
    }

};

class FCFS_Scheduler {
public:
    FCFS_Scheduler(int coreCount, int processCount, ConsoleManager* consoleManager);

    void start();
    void stop();

private:
    int coreCount;
    int processCount;
    atomic<bool> running;
    vector<thread> cpuWorkers;
    thread schedulerThread;
    queue<Process*> processQueue;
    mutex queueMutex;
    condition_variable cv;

    ConsoleManager* consoleManager; // Store reference to ConsoleManager

    void schedulerFunction();
    void cpuWorker(int coreId);
};

#endif // FCFS_H


