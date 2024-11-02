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
    bool dummy;
    int total_ins;
    string name;

    Process(int pid) : id(pid), dummy(true) {}
    Process(string name) : name(name), dummy(false) {}
};

class FCFS_Scheduler {
public:
    FCFS_Scheduler(int coreCount, int min_ins, int max_ins, ConsoleManager* consoleManager);

    void start();
    void schedulingTestStart(bool run);
    void stop();
    void addToQueue(string name);

private:
    int coreCount;
    int processCount;
    int min_ins;
    int max_ins;
    atomic<bool> running;
    vector<thread> cpuWorkers;
    thread schedulerThread;
    thread schedulingTestThread;
    queue<Process*> processQueue;
    mutex queueMutex;
    condition_variable cv;

    ConsoleManager* consoleManager; // Store reference to ConsoleManager

    void schedulerFunction();
    void cpuWorker(int coreId);
};

#endif // FCFS_H


