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
#include <arpa/inet.h>
#include <semaphore.h>

#include "Serializable.hpp"
#include "Socket.hpp"

namespace flip {
    typedef std::function<void(flip::serialStream __stream)> __FLIP_route;
    typedef std::unordered_map<std::string, __FLIP_route> __FLIP_routeMap;

    class App {
        private:
            const std::string &_name;
            const __FLIP_routeMap &_routesMap;

            Socket _serverSocket;

            struct ClientData {
                std::queue<std::string> fifo;
            };

            std::mutex _mutex;
            sem_t requests;
            std::unordered_map<std::string, ClientData> _clientDataMap;
        public:
            void handleClient(const Socket);
            App(uint16_t, const std::string &, const __FLIP_routeMap &);
            ~App(void);
            void run(void);
            const __FLIP_route &operator [](const std::string &);
            void requestAnalyser(void);
            void route(const serialStream &);
    };
}
