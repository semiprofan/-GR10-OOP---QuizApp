// =========================================================================
// File: Timer.h
// Huynh Nhat Khanh
// Nhiem vu: Xay dung Class Timer tinh thoi gian.
// =========================================================================
#pragma once
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
    // Ham bat dau dem gio va luu lai thoi diem bat dau thuc te
    void start() {
        startTime = system_clock::now();
        start_time_t = system_clock::to_time_t(startTime);
    }

    // Ham tinh toan va tra ve thoi gian da troi qua (tinh bang giay)
    double getElapsedTime() {
        auto endTime = system_clock::now();
        duration<double> elapsed = endTime - startTime;
        return elapsed.count(); 
    }

    // Ham chuyen doi thoi gian bat dau thanh chuoi dinh dang doc duoc
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