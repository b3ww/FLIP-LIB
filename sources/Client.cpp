/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Client.cpp
*/

#include "Client.hpp"
#include <iostream>

namespace flip {
    Client::Client(const std::string &ip, const uint16_t &port):
        _ip(ip), _port(port)
    {
        sem_init(&_pendingRequests, 0, 0);
    }

    void Client::newRequest(const Request &request)
    {
        // std::thread requestThread(&Client::handleRequest, this, request);
        // requestThread.detach();
        handleRequest(request);
    }


    void Client::handleRequest(const Request &request)
    {
        Socket socket(_ip, _port);
        std::string data(request.getPayload().serialize());
        socket.send(data);
        std::cout << socket.getFd() << std::endl;
        // socket.receive();
    }
}
