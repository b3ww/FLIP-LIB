/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** App.hpp
*/

#pragma once

#include <unordered_map>
#include <functional>
#include <string>
#include <memory>
#include <map>
#include <queue>
#include <mutex>
#include <semaphore.h>

#include "Serializable.hpp"
#include "Socket.hpp"

namespace flip {
    /**
     * @brief Alias for the return type of a route function.
     */
    typedef std::pair<uint16_t, serialStream> __FLIP_routeReturnType;

    /**
     * @brief Alias for the route function signature.
     */
    typedef std::function<__FLIP_routeReturnType(flip::serialStream __stream)> __FLIP_route;

    /**
     * @brief Alias for the map containing route handlers.
     */
    typedef std::unordered_map<std::string, __FLIP_route> __FLIP_routeMap;

    /**
     * @brief Represents the main application class.
     */
    class App {
        private:
            const std::string &_name; ///< The name of the application.
            const __FLIP_routeMap &_routesMap; ///< The map containing route handlers.
            Socket _serverSocket; ///< The server socket.

        public:
            /**
             * @brief Handles a client request.
             * @param socket The client socket.
             */
            void handleClient(const Socket &socket);

            /**
             * @brief Constructs an App object.
             * @param port The port number to listen on.
             * @param name The name of the application.
             * @param routesMap The map containing route handlers.
             */
            App(uint16_t port, const std::string &name, const __FLIP_routeMap &routesMap);

            /**
             * @brief Destroys the App object.
             */
            ~App(void);

            /**
             * @brief Runs the application.
             */
            void run(void);

            /**
             * @brief Overloaded subscript operator to access route handlers.
             * @param name The name of the route.
             * @return The route handler function.
             */
            const __FLIP_route &operator [](const std::string &name);

            /**
             * @brief Routes a request to the appropriate handler.
             * @param socket The client socket.
             * @param serialized The serialized request data.
             */
            void route(const Socket &socket, const serialStream &serialized);
    };
}
