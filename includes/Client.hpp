/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Client.hpp
*/

#pragma once

#include <string>
#include <limits>
#include <queue>

#include "Serializable.hpp"
#include "Payload.hpp"
#include "Socket.hpp"
#include "Request.hpp"

namespace flip {
    class Client {
        public:
            Client(const std::string &, const uint16_t &);
            ~Client() = default;

            void addToSendRequest(const Request &request);

        private:
            std::string _ip;
            uint16_t _port;

            std::queue<std::pair<Socket, Request>> _toSendRequests;
            std::queue<std::pair<Socket, Request>> _pendingRequests;
            std::queue<Request> _callbackRequests;
    };

    void operator>>(const Request &request, Client client)
    {
        client.addToSendRequest(request);
    }
}
