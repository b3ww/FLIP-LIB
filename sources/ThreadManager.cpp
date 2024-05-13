/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** ThreadManager.cpp
*/

#include "ThreadManager.hpp"

namespace flip {
    ThreadManager::ThreadManager() :
        _newThread(0),
        _manager(&ThreadManager::managerRoutine, this)
    {
    }

    ThreadManager::~ThreadManager()
    {
        waitThreads();
        _running = false;
        _newThread.release();
        if (_manager.joinable()) {
            _manager.join();
        }
    }

    void ThreadManager::deleteThread()
    {
        _mutex.lock();
        for (auto it = _threads.begin(); it != _threads.end(); it++) {
            auto &thread = *it;
            if (thread.joinable()) {
                thread.join();
                _threads.erase(it);
                _mutex.unlock();
                _newThread.acquire();
                return;
            }
        }
        _mutex.unlock();
    }

    void ThreadManager::managerRoutine()
    {
        _newThread.acquire();
        while (_running) {
            deleteThread();
        }
    }

    void ThreadManager::newThread(std::thread &thread)
    {
        _mutex.lock();
        _threads.push_back(std::move(thread));
        _mutex.unlock();
        _newThread.release();
    }

    size_t ThreadManager::getNbThreads(void)
    {
        _mutex.lock();
        size_t nb = _threads.size();
        _mutex.unlock();
        return nb;
    }

    void ThreadManager::waitThreads(size_t cap)
    {
        while (getNbThreads() > cap) {}
    }
}