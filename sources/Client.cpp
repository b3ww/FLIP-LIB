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
    }

    void Client::newRequest(const Request &request)
    {
        std::thread requestThread(&Client::handleRequest, this, request);
        _thManager.newThread(requestThread);
    }


    void Client::handleRequest(const Request &request)
    {
        Socket socket(_ip, _port);
        std::string data(request.getPayload().serialize());
        socket.send(data);
        std::cout << socket.getFd() << std::endl;
        std::string response(socket.receive());

        if (!response.size())
            throw Exception("Socket closed - no request response");
    }
}
