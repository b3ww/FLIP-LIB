/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Exceptions.hpp
*/

#pragma once

#include <exception>
#include <string>

namespace flip {
    /**
     * @brief Custom exception class for the FLIP library.
     *
     * This exception class is used to report specific errors
     * in the FLIP library.
     */
    class Exception : public std::exception {
        public:
            /**
             * @brief Constructor of the exception.
             *
             * @param message The error message associated with this exception.
             */
            Exception(const std::string& message) : _message(message) {}

            /**
             * @brief Get the error message associated with this exception.
             *
             * @return const char* A pointer to a character string containing the error message.
             */
            const char* what() const noexcept override {
                return _message.c_str();
            }

        private:
            std::string _message; ///< The error message associated with this exception.
    };
}
