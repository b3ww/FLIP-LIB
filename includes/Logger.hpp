/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Logger.hpp
*/

#pragma once

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <cstdint>

namespace flip {

    enum class LogLevel {
        INFO,
        WARNING,
        ERROR,
        DEBUG
    };

    class Logger {
        private:
            const std::string _name;
            std::unordered_map<LogLevel, std::ostream *> _streams;
            std::string fomrmatLogLevel(const LogLevel &) const;

        public:
            Logger(const std::string &);
            std::ostream &operator()(LogLevel);
            void setup(const LogLevel &, std::ostream &);
    };
}
