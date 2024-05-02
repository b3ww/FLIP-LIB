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

    int request(const serialStream &)
    {
    }
}
