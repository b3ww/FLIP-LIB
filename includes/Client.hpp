/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Client.hpp
*/

#pragma once

#include <string>
#include "Serializable.hpp"
#include "Payload.hpp"
#include "Socket.hpp"
#include "Request.hpp"
#include "ThreadManager.hpp"
#include "Exceptions.hpp"

namespace flip {
    /**
     * @brief Represents a client for making requests to a server.
     */
    class Client {
        public:
            /**
             * @brief Constructs a Client object with the specified IP address and port.
             * @param ip The IP address of the server.
             * @param port The port of the server.
             */
            Client(const std::string &ip, const uint16_t &port);

            /**
             * @brief Default destructor.
             */
            ~Client() = default;

            /**
             * @brief Creates a new request and handles it.
             * @param request The request to handle.
             */
            void newRequest(const Request &request);

            /**
             * @brief Handles a request.
             * @param request The request to handle.
             */
            void handleRequest(const Request &request);

            /**
             * @brief Sends a request with a serializable payload and callbacks.
             * @tparam T The type of the serializable payload.
             * @param routeName The name of the route.
             * @param serializable The serializable payload.
             * @param callbacks The callback manager.
             */
            template <typename T>
            void request(const std::string &routeName, const T &serializable, const CallbackManager &callbacks)
            {
                Payload payload(routeName, 0, serializable.serialize());
                Request request(payload, callbacks);

                if (!std::is_base_of_v<Serializable, T>)
                    throw ClientException("T is not serializable");
                newRequest(request);
            }

            /**
             * @brief Get current number of requests.
             */
            size_t getNbRequests(void) {return _thManager.getNbThreads();}

            /**
             * @brief Wait for the total number of request to go down to a specified number of request.
             * @param cap The number of request specified. 0 by default.
             */

            void waitRequests(size_t cap = 0) {_thManager.waitThreads(cap);}
        private:
            std::string _ip; ///< The IP address of the server.
            uint16_t _port; ///< The port of the server.
            ThreadManager _thManager; ///< The thread manager.
    };

    /**
     * @brief Overloaded operator for sending a request to a client.
     * @param request The request.
     * @param client The client to send the request to.
     */
    void operator>>(const Request &request, Client &client);
}
