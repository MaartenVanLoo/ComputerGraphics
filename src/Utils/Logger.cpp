
#include "Utils/Logger.h"

//
// Created by maart on 3/11/2022.
//
Logger::LogLevel Logger::level = Logger::LogLevel::log_warning;
std::mutex Logger::coutMutex = std::mutex();

void Logger::warning(std::string_view message) {
    if (Logger::level<LogLevel::log_warning) return;
    std::lock_guard<std::mutex> lockGuard(coutMutex);
    std::cout << "[WARNING]\t" << message << "\n";
}
void Logger::error(std::string_view message) {
    if (Logger::level<LogLevel::log_error) return;
    std::lock_guard<std::mutex> lockGuard(coutMutex);
    std::cout << "[ERROR  ]\t" << message << "\n";
}

void Logger::info(std::string_view message) {
    if (Logger::level<LogLevel::log_info) return;
    std::lock_guard<std::mutex> lockGuard(coutMutex);
    std::cout << "[INFO   ]\t" << message << "\n";
}


