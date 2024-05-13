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
    _name(name), _routesMap(routesMap), _logger("App {" + name + "}")
    {
    }

    App::~App()
    {
    }

    void App::run(uint16_t port)
    {
        _serverSocket.bindPort(port);
        _logger(LogLevel::INFO) << "Application si Sarting" << std::endl;
        for (const auto &pair: _routesMap) {
            _logger(LogLevel::DEBUG) << "find route -> [" << pair.first << "]" << std::endl;
        }
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

        route(clientSocket, buffer, clientID);
    }

    void App::route(const Socket &socket, const serialStream &serialized, const std::string &clientID)
    {
        Payload payload;

        try {
            payload.deserialize(serialized);
        } catch (const Exception &e) {
            _logger(LogLevel::WARNING) << clientID << " failed to deserialize payload ->" << e.what() << std::endl;
            return;
        }
        std::string routeName(payload.getRouteName());
        std::pair<uint16_t, serialStream> usefull;
        std::string nullString(64, '_');
        routeName.erase(std::remove_if(routeName.begin(), routeName.end(), [](char c) {
            return !isprint(c);
        }), routeName.end());

        _logger(LogLevel::INFO) << clientID << " request route [" << routeName << "]" << std::endl;
        auto it = _routesMap.find(routeName);
        try {
            if (it == _routesMap.end())
                throw Exception("route not found");
            usefull = it->second(payload.getSerialized(), socket.getID());
        } catch (const Exception &e)  {
            _logger(LogLevel::WARNING) << clientID << " route excetion -> " << e.what() << std::endl;
            usefull = std::make_pair<uint16_t, serialStream>(42, std::string(e.what()));
        }
        SerialUint16 code(usefull.first);
        Payload n(nullString, code, usefull.second);
        socket.send(n.serialize());
    }
}
