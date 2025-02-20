#pragma once
#include <iostream>
#include <fstream>
#include <mutex>
#include <ctime>

using namespace std;

class Logger {
public:
    enum LogLevel {
        INFO,
        WARNING,
        ERROR
    };

    explicit Logger(const string& filename);
    ~Logger();

    void log(LogLevel level, const string& message);

private:
    ofstream logFile;
    mutex logMutex;

    string getCurrentTime();
    string logLevelToString(LogLevel level);
};

