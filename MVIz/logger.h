#ifdef LOGGER

#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sys/stat.h>

enum Severity {
    Fatal,
    Error,
    Warning,
    Info,
    Debug,
};

std::string CurrentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y/%m/%d %X", &tstruct);

    return buf;
}

std::string CurrentDate() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y%m%d", &tstruct);

    return buf;
}

class Logger {
    public: 
        ~Logger() {}

        static void Log(std::string message, Severity level, std::ios_base::openmode mode = std::ios::app) {
            std::ios::app;
            std::ofstream file(filepath, mode);

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

        static void RestoreDefaultFilepath() {
            filepath = "log.txt";
        }

        static std::string GetFilepath() {
            return filepath;
        }


        static void RotateLogs() {
            if (lastRotationDate != CurrentDate()) {
                lastRotationDate = CurrentDate();
                std::string oldFile = filepath;

                // remove extension
                for (int i = 0; i < oldFile.length(); i++) {
                    if (oldFile[i] == '.') {
                        oldFile.erase(i, 4);
                    }
                }

                // add new extension
                oldFile = oldFile + "_" + CurrentDate() + ".log";
                if (rename(filepath.c_str(), oldFile.c_str()) != 0) {
                    std::cerr << "Error Moving File: " << strerror(errno) << std::endl;
                }
            }
        }
        // long long to avoid potential overflow issues though we can just use int here for now
        static long long GetFileSize() {
            struct stat stat_buf;
            int rc = stat(filepath.c_str(), &stat_buf);
            return rc == 0 ? stat_buf.st_size : -1;
        }

    private:
        static std::string filepath;
        static std::string lastRotationDate;
};

// This file is created in whichever directory the Logger::Log(...) function
// called.
// Need to find a better way for this.
// Or need to check it's behavior when ran with the entire program.
std::string Logger::filepath = "log.txt";
std::string Logger::lastRotationDate = CurrentDate();

#endif