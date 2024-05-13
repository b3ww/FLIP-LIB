/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Logger.cpp
*/

#include "Logger.hpp"

namespace flip {
    Logger::Logger(const std::string &name): _name(name)
    {
        _streams = {
            {LogLevel::INFO, &std::cout},
            {LogLevel::WARNING, &std::cout},
            {LogLevel::ERROR, &std::cout},
            {LogLevel::DEBUG, &std::cout}
        };
    }

    std::string Logger::fomrmatLogLevel(const LogLevel &level) const
    {
        switch (level) {
            case LogLevel::INFO:
                return "\033[32m[INFO] \033[0m=> ";
            case LogLevel::WARNING:
                return "\033[35m[WARNING] \033[0m=> ";
            case LogLevel::ERROR:
                return "\033[31m[ERROR] \033[0m=> ";
            case LogLevel::DEBUG:
                return "\033[33m[DEBUG] \033[0m=> ";
            default:
                return "";
        }
    }

    std::ostream &Logger::operator()(LogLevel level)
    {
        return *_streams[level] << "\033[97;4;34mFLIP LOG\033[0m ("<< _name
        <<") " << fomrmatLogLevel(level);
    }

    void Logger::setup(const LogLevel &key, std::ostream &stream)
    {
        auto it = _streams.find(key);
        if (it != _streams.end()) {
            it->second = &stream;
        } else {
            _streams.insert({key, &stream});
        }
    }
}