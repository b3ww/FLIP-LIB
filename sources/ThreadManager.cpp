/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** ThreadManager.cpp
*/

#include "ThreadManager.hpp"

namespace flip {
    ThreadManager::ThreadManager() :
        _manager(&ThreadManager::managerRoutine, this)
    {
        sem_init(&_newThread, 0, 0);
    }

    ThreadManager::~ThreadManager()
    {
        _running = false;
        sem_post(&_newThread);
        if (_manager.joinable()) {
            _manager.join();
        }
        for (auto &thread : _threads) {
            thread.join();
        }
        sem_destroy(&_newThread);
    }

    void ThreadManager::managerRoutine()
    {
        sem_wait(&_newThread);
        while (_running) {
            for (auto it = _threads.begin(); it != _threads.end(); it++) {
                auto &thread = *it;
                if (thread.get_id() == std::thread::id()) {
                    thread.join();
                    sem_wait(&_newThread);
                    break;
                }
            }
        }
    }

    void ThreadManager::newThread(std::thread &thread)
    {
        _threads.push_back(std::move(thread));
        sem_post(&_newThread);
    }
}