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
#include "Payload.hpp"

namespace flip {
    App::App(uint16_t port, const std::string &name, const __FLIP_routeMap &routesMap) :
    _name(name), _routesMap(routesMap), _serverSocket(port)
    {
        sem_init(&requests, 1, 0);
    }

    App::~App()
    {
    }

    void App::run()
    {
        std::thread printingThread(&App::requestAnalyser, this);
        printingThread.detach();

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

    void App::requestAnalyser(void)
    {
        while (true) {
            sem_wait(&requests);
            for (auto& [clientId, clientData] : _clientDataMap) {
                std::unique_lock<std::mutex> lock(_mutex);
                auto& clientFIFO = clientData.fifo;
                if (!clientFIFO.empty()) {
                    while (!clientFIFO.empty()) {
                        route(clientFIFO.front());
                        clientFIFO.pop();
                    }
                }
                lock.unlock();
            }
        }
    }

    void App::handleClient(const Socket clientSocket)
    {
        std::string clientID = clientSocket.getID();
        std::string buffer = clientSocket.receive();
        std::unique_lock<std::mutex> lock(_mutex);

        _clientDataMap[clientID].fifo.push(buffer);
        lock.unlock();
        sem_post(&requests);
    }

    void App::route(const serialStream &serialized)
    {
        Payload payload(serialized);
        std::string routeName(payload.getRouteName());
        routeName.erase(std::remove_if(routeName.begin(), routeName.end(), [](char c) {
            return !isprint(c);
        }), routeName.end());

        auto it = _routesMap.find(routeName);
        if (it == _routesMap.end())
            throw std::invalid_argument("route not found");
        else
            it->second(payload.getSerialized());
    }
}
