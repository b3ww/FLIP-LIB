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

    void Client::addToSendRequest(const Request &request)
    {
        _toSendRequests.push(std::make_pair(Socket(_ip, _port), request));
    }
}
