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
    /**
     * @brief Class responsible for managing threads.
     *
     * This class creates and manages threads for handling requests.
     */
    class ThreadManager {
        public:
            /**
             * @brief Constructor for the ThreadManager class.
             */
            ThreadManager();

            /**
             * @brief Destructor for the ThreadManager class.
             */
            ~ThreadManager();

            /**
             * @brief Routine function for managing threads.
             */
            void managerRoutine();

            /**
             * @brief Add a new thread to the manager.
             * @param thread The new thread to add.
             */
            void newThread(std::thread &thread);

        private:
            std::thread _manager; /**< The thread manager thread */
            std::vector<std::thread> _threads; /**< Vector storing all threads managed by the manager */

            sem_t _newThread; /**< Semaphore to signal the addition of a new thread */
            bool _running = true; /**< Flag indicating whether the manager is running */
    };
}
