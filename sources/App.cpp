/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** App.cpp
*/

#include "App.hpp"
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <mutex>
#include <queue>
#include "Socket.hpp"
#include "Payload.hpp"
#include "Exceptions.hpp"

namespace flip {
    App::App(const std::string &name, const __FLIP_routeMap &routesMap) :
    _name(name), _routesMap(routesMap)
    {
    }

    App::~App()
    {
    }

    void App::run(uint16_t port)
    {
        _serverSocket.bindPort(port);
        while (true) {
            try {
                Socket clientSocket(_serverSocket.accept());
                std::thread clientThread([this, clientSocket](){
                    handleClient(clientSocket);
                });
                clientThread.detach();
            } catch (...) {
            }
        };
    }

    void App::handleClient(const Socket &clientSocket)
    {
        std::string clientID = clientSocket.getID();
        std::string buffer = clientSocket.receive();

        route(clientSocket, buffer);
    }

    void App::route(const Socket &socket, const serialStream &serialized)
    {
        Payload payload(serialized);
        std::string routeName(payload.getRouteName());
        std::pair<uint16_t, serialStream> usefull;
        std::string nullString(64, '_');
        routeName.erase(std::remove_if(routeName.begin(), routeName.end(), [](char c) {
            return !isprint(c);
        }), routeName.end());

        auto it = _routesMap.find(routeName);
        try {
            if (it == _routesMap.end())
                throw Exception("route not found");
            usefull = it->second(payload.getSerialized());
        } catch (const Exception &e)  {
            usefull = std::make_pair<uint16_t, serialStream>(42, std::string(e.what()));
        }
        SerializableUint16 code(usefull.first);
        Payload n(nullString, code, usefull.second);
        socket.send(n.serialize());
    }
}
