/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Client.hpp
*/

#pragma once

#include <string>
#include <limits>
#include <thread>
#include <semaphore.h>
#include <queue>
#include <iostream>

#include "Serializable.hpp"
#include "Payload.hpp"
#include "Socket.hpp"
#include "Request.hpp"
#include "ThreadManager.hpp"

namespace flip {
    class Client {
        public:
            Client(const std::string &, const uint16_t &);
            ~Client() = default;

            void newRequest(const Request &request);
            void handleRequest(const Request &request);
        private:
            std::string _ip;
            uint16_t _port;

            ThreadManager _thManager;
    };

    void operator>>(const Request &request, Client &client)
    {
        client.newRequest(request);
    }
}
