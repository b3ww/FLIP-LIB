/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Socket.cpp
*/

#include "Socket.hpp"
#include <iostream>

namespace flip {
    Socket::Socket(const std::string &ip, const uint16_t &port) :
        _fd (socket(AF_INET, SOCK_STREAM, 0))
    {
        if (_fd == -1)
            throw;

        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(port);

        if (inet_pton(AF_INET, ip.c_str(), &_addr.sin_addr) <= 0)
            throw;
        if (connect(_fd, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr)) == -1)
            throw;
    }

    Socket::Socket(const uint16_t &port) :
        _fd(socket(AF_INET, SOCK_STREAM, 0))
    {
        if (_fd == -1)
            throw;

        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = INADDR_ANY;
        _addr.sin_port = htons(port);

        if (bind(_fd, reinterpret_cast<sockaddr *>(&_addr), sizeof(_addr)) == -1)
            throw;

        if (listen(_fd, SOMAXCONN) == -1)
            throw;
    }

    Socket::Socket(int acceptFd)
    {
        socklen_t len = sizeof(_addr);

        _fd = (::accept(acceptFd, reinterpret_cast<sockaddr *>(&_addr), &len));
        if (_fd < 0)
            throw;
    }

    Socket::Socket(const Socket &other) :
        _fd(dup(other._fd)),
        _addr(other._addr)
    {
        if (_fd < 0)
            throw;
    }

    Socket::~Socket()
    {
        if (_fd != -1)
            close(_fd);
    }

    Socket Socket::accept() const
    {
        return Socket(_fd);
    }

    void Socket::send(const std::string& data) const
    {
        std::cout << data << std::endl;
        if (::send(_fd, data.c_str(), data.size(), 0) == -1)
            throw;
    }

    std::string Socket::receive(void) const
    {
        char buffer[BUFFER_SIZE];
        ssize_t nb_bytes = 0;

        nb_bytes = recv(_fd, buffer, BUFFER_SIZE - 1, 0);
        if (nb_bytes == -1)
            throw;
        return std::string(buffer, nb_bytes);
    }
}