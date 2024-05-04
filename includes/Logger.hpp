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
        NONE,
        INFO,
        WARNING,
        ERROR,
        DEBUG
    };

    class Logger {
        private:
            std::unordered_map<LogLevel, std::ostream *> _streams;

        public:
            Logger();
            std::ostream &operator()(LogLevel level);
            void setup(const LogLevel &key, std::ostream &stream);
    };
}
