/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** ThreadManager.hpp
*/

#pragma once

#include <thread>
#include <vector>
#include <iostream>
#include <semaphore.h>

namespace flip {
    class ThreadManager {
        public:
            ThreadManager();
            ~ThreadManager();

            void managerRoutine();
            void newThread(std::thread &);
        private:
            std::thread _manager;
            std::vector<std::thread> _threads;

            sem_t _newThread;
            bool _running = true;
    };
}