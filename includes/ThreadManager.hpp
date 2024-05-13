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
#include <semaphore>
#include <mutex>

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

            // /**
            //  * @brief Wait to join all running thread of the ThreadManager class.
            //  * Cannot call newThread until it ends;
            //  */
            // void waitThreads();
            /**
             * @brief Routine function for managing threads.
             */
            void deleteThread();
            void managerRoutine();

            /**
             * @brief Add a new thread to the manager.
             * @param cap The new thread to add.
             */
            void newThread(std::thread &thread);

            /**
             * @brief Get current number of thread.
             */
            size_t getNbThreads(void);

            /**
             * @brief Wait for the total number of thread to go down to a specified number of thread.
             * @param thread The number of thread specified. 0 by default.
             */
            void waitThreads(size_t cap = 0);

        private:
            std::vector<std::thread> _threads; /**< Vector storing all threads managed by the manager */

            std::mutex _mutex;

            std::counting_semaphore<0> _newThread; /**< Semaphore to signal the addition of a new thread */
            bool _running = true; /**< Flag indicating whether the manager is running */

            std::thread _manager; /**< The thread manager thread */
    };
}
