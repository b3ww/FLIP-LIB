/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Client.cpp
*/

#include "Client.hpp"

namespace flip {
    Client::Client(const std::string &ip, const uint16_t &port):
        _ip(ip), _port(port)
    {
        sem_init(&_pendingRequests, 0, 0);
    }

    void Client::newRequest(const Request &request)
    {
        std::thread requestThread(&handleRequest, this, request);
        requestThread.detach();
    }

    void Client::handleRequest(const Request &request)
    {
        sem_post(&_pendingRequests);
        Socket socket(_ip, _port);
        std::string data(request.getPayload().serialize().data());

        socket.send(data);

        sem_wait(&_pendingRequests);
    }
}
