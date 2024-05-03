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
    /**
     * @brief Socket class for network communication.
     *
     * This class provides functionalities for socket communication over the network.
     */
    class Socket {
        public:
            /**
             * @brief Constructor for creating a socket with a specified IP address and port.
             *
             * @param ip The IP address to bind the socket to.
             * @param port The port number to bind the socket to.
             */
            Socket(const std::string& ip, const uint16_t& port);

            /**
             * @brief Constructor for creating a socket with a specified port (using any available IP address).
             *
             * @param port The port number to bind the socket to.
             */
            Socket(const uint16_t& port);

            /**
             * @brief Copy constructor.
             *
             * @param other The socket object to copy from.
             */
            Socket(const Socket& other);

            /**
             * @brief Destructor.
             */
            ~Socket();

            /**
             * @brief Accepts an incoming connection and returns a new Socket object representing the connection.
             *
             * @return Socket A new Socket object representing the accepted connection.
             */
            Socket accept() const;

            /**
             * @brief Sends data over the socket.
             *
             * @param data The data to send.
             */
            void send(const std::string& data) const;

            /**
             * @brief Receives data from the socket.
             *
             * @return std::string The received data.
             */
            std::string receive() const;

            /**
             * @brief Gets the file descriptor associated with the socket.
             *
             * @return int The file descriptor associated with the socket.
             */
            int getFd() const { return _fd; }

            /**
             * @brief Gets the ID (IP address and port) associated with the socket.
             *
             * @return std::string The ID associated with the socket.
             */
            std::string getID() const { return std::string(std::string(inet_ntoa(_addr.sin_addr)) + ':' + std::to_string(ntohs(_addr.sin_port))); }

        private:
            int _fd; ///< File descriptor associated with the socket.
            sockaddr_in _addr; ///< Address information associated with the socket.

            /**
             * @brief Private constructor for creating a socket using an accepted file descriptor.
             *
             * @param acceptFd The file descriptor representing the accepted connection.
             */
            Socket(int acceptFd);
    };
}
