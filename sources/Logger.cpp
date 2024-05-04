/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Logger.cpp
*/

#include "Logger.hpp"

namespace flip {
    Logger::Logger()
    {
        _streams = {
            {LogLevel::NONE, &std::cout},
            {LogLevel::INFO, &std::cout},
            {LogLevel::WARNING, &std::cout},
            {LogLevel::ERROR, &std::cout},
            {LogLevel::DEBUG, &std::cout}
        };
    }

    std::ostream &Logger::operator()(LogLevel level)
    {
        return *_streams[level] << "LOG: ";
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