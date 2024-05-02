/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Client.hpp
*/

#pragma once

#include <string>

namespace flip {
    class Client {
        private:
            struct appInfo {
                std::string _ip;
                uint16_t _port;
                public:
                    appInfo(const std::string &ip, uint16_t port): _ip(ip), _port(port) {}
            } _app;

        public:
            Client();
    };
}