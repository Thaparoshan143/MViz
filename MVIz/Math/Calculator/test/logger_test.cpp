#include "../../../logger.h"

int main() {
    Logger::Log("hello", Severity::Info);
    Logger::Log("hello", Severity::Debug);
    Logger::Log("hello", Severity::Error);
    Logger::Log("hello", Severity::Fatal);
    Logger::Log("hello", Severity::Warning);
    return 0;
}