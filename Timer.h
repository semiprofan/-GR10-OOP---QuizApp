// =========================================================================
// File: Timer.h
// Huynh Nhat Khanh
// Nhiem vu: Xay dung Class Timer tinh thoi gian.
// =========================================================================
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <ctime>
#include <string>

using namespace std;
using namespace std::chrono;

class Timer {
private:
    system_clock::time_point startTime;
    time_t start_time_t; 

public:
    void start() {
        startTime = system_clock::now();
        start_time_t = system_clock::to_time_t(startTime);
    }

    double getElapsedTime() {
        auto endTime = system_clock::now();
        duration<double> elapsed = endTime - startTime;
        return elapsed.count(); 
    }

    string getStartTimeString() {
        char buffer[26];
        #ifdef _MSC_VER 
            ctime_s(buffer, sizeof(buffer), &start_time_t);
        #else
            string timeStr = ctime(&start_time_t);
            return timeStr;
        #endif
        return string(buffer);
    }
};

#endif