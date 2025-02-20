#include "Logger.h"

Logger::Logger(const string& filename) : logFile(filename, ios::app) {
    if (!logFile.is_open()) {
        cerr << "Khong the mo file log: " << filename << endl;
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(LogLevel level, const string& message) {
    lock_guard<mutex> guard(logMutex);
    if (logFile.is_open()) {
        logFile << getCurrentTime() << " [" << logLevelToString(level) << "] " << message << endl;
    }
}

string Logger::getCurrentTime() {
    time_t now = time(nullptr);
    struct tm timeInfo;
    char buf[100];

    localtime_s(&timeInfo, &now);  
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeInfo);

    return buf;
}

string Logger::logLevelToString(LogLevel level) {
    switch (level) {
    case INFO: return "INFO";
    case WARNING: return "WARNING";
    case ERROR: return "ERROR";
    default: return "UNKNOWN";
    }
}