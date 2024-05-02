/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Socket.hpp
*/

#pragma once

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

#define BUFFER_SIZE 4096

namespace flip {
    class Socket {
        public:
            Socket(const std::string& ip, uint16_t port);
            Socket(uint16_t port);
            ~Socket();

            Socket accept(void) const;

            void send(const std::string& data) const;
            std::string receive(void) const;

            int getFd(void) const {return _fd;}
            std::string getID(void) const {return std::string(std::string(inet_ntoa(_addr.sin_addr)) + ':' + std::to_string(ntohs(_addr.sin_port)));}
        private:
            int _fd;
            sockaddr_in _addr;

            Socket(int acceptFd);
    };
}