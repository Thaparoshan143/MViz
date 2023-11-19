#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

enum Severity {
    Fatal,
    Error,
    Warning,
    Info,
    Debug,
};

std::string CurrentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y/%m/%d %X", &tstruct);

    return buf;
}

class Logger {
    public: 
        static void Log(std::string message, Severity level) {
            std::ofstream file(filepath, std::ios::app);

            file << CurrentDateTime();

            switch (level) {
                case Fatal:         file << std::setw(4) << " " << "[FATAL]" << std::setw(4) << " ";      break;
                case Error:         file << std::setw(4) << " " << "[ERROR]" << std::setw(4) << " ";       break;
                case Warning:       file << std::setw(4) << " " << "[WARNING]" << std::setw(4) << " ";     break;
                case Info:          file << std::setw(4) << " " << "[INFO]" << std::setw(4) << " ";         break;
                case Debug:         file << std::setw(4) << " " << "[DEBUG]" << std::setw(4) << " ";       break;
            }

            file << message << "\n";
            file.close();
        }

        static void SetFilepath(std::string path) {
            filepath = path;
        }

        static std::string GetFilepath() {
            return filepath;
        }

        ~Logger() {}
    private:
        static std::string filepath;
};

// This file is created in whichever directory the Logger::Log(...) function
// called.
// Need to find a better way for this.
// Or need to check it's behavior when ran with the entire program.
std::string Logger::filepath = "log.txt";

