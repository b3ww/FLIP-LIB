/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** App.cpp
*/

#include "App.hpp"
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <mutex>
#include <queue>

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
                std::shared_ptr<Socket> clientSocketPtr(new Socket(_serverSocket.accept()));
                std::thread clientThread(&App::handleClient, this, std::shared_ptr<Socket>(clientSocketPtr));
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
                        std::cout << clientFIFO.front() << std::endl;
                        clientFIFO.pop();
                    }
                }
                lock.unlock();
            }
        }
    }

    void App::handleClient(std::shared_ptr<Socket> clientSocketPtr)
    {
        Socket &clientSocket = *clientSocketPtr;
        std::string clientID = clientSocket.getID();

        std::cout << "Connection: " << clientID << std::endl;

        std::string buffer = clientSocket.receive();
        std::unique_lock<std::mutex> lock(_mutex);
        _clientDataMap[clientID].fifo.push(buffer);
        lock.unlock();
        sem_post(&requests);

        std::cout << clientID << " disconnected" << std::endl;
    }
}
