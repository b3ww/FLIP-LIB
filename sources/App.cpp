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
    _name(name), _routesMap(routesMap)
    {
        sem_init(&requests, 1, 0);
        _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (_serverSocket < 0) {
            exit(EXIT_FAILURE);
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);

        if (bind(_serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
            close(_serverSocket);
            exit(EXIT_FAILURE);
        }

        if (listen(_serverSocket, SOMAXCONN) < 0) {
            close(_serverSocket);
            exit(EXIT_FAILURE);
        }
    }

    App::~App()
    {
        if(_serverSocket != -1)
            close(_serverSocket);
    }

    void App::run()
    {
        std::thread printingThread(&App::requestAnalyser, this);
        printingThread.detach();

        while (true) {
            sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            int clientSocket = accept(_serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
            if (clientSocket < 0)
                continue;
            std::string ip = inet_ntoa(clientAddr.sin_addr);
            int port = ntohs(clientAddr.sin_port);

            std::string clientId = ip + ":" + std::to_string(port);

            std::thread clientThread(&App::handleClient, this, clientSocket, clientAddr);
            clientThread.detach();
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

    void App::handleClient(int clientSocket, sockaddr_in clientAddr)
    {
        std::string ip = inet_ntoa(clientAddr.sin_addr);
        std::string clientId = ip + ":" + std::to_string(ntohs(clientAddr.sin_port));
        std::cout << "Connection" << clientId << std::endl;
        char buffer[4096];
        int bytesRead;

        while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
            std::unique_lock<std::mutex> lock(_mutex);
            _clientDataMap[clientId].fifo.push(std::string(buffer, bytesRead));
            lock.unlock();
        }
        sem_post(&requests);

        if (!bytesRead)
            std::cout << clientId << "disconnected" << std::endl;

        close(clientSocket);
    }
}
