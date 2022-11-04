//
// Created by maart on 3/11/2022.
//

#ifndef I_COMPUTERGRAPHICS_LOGGER_H
#define I_COMPUTERGRAPHICS_LOGGER_H
#include <string>
#include <iostream>
#include <mutex>


class Logger{

public:
    enum LogLevel{
        log_none = -1,
        log_info = 0,
        log_warning = 1,
        log_error = 2
    };
    static std::mutex coutMutex;
    static LogLevel level;
    static void warning(std::string_view message);
    static void info(std::string_view message);
    static void error(std::string_view message);
};

#endif //I_COMPUTERGRAPHICS_LOGGER_H
