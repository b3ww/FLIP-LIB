/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Exceptions.hpp
*/

#pragma once

#include <exception>
#include <iostream>
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
            Exception(const std::string& message) : _message("flipError: " + message) {}

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

    /**
     * @brief Exception class for application-related errors.
     */
    class AppException : public Exception {
        public:
            AppException(const std::string& message) : Exception("AppException: " + message) {}
    };

    /**
     * @brief Exception class for callback-related errors.
     */
    class CallbackException : public Exception {
        public:
            CallbackException(const std::string& message) : Exception("CallbackException: " + message) {}
    };

    /**
     * @brief Exception class for client-related errors.
     */
    class ClientException : public Exception {
        public:
            ClientException(const std::string& message) : Exception("ClientException: " + message) {}
    };

    /**
     * @brief Exception class for payload-related errors.
     */
    class PayloadException : public Exception {
        public:
            PayloadException(const std::string& message) : Exception("PayloadException: " + message) {}
    };

    /**
     * @brief Exception class for request-related errors.
     */
    class RequestException : public Exception {
        public:
            RequestException(const std::string& message) : Exception("RequestException: " + message) {}
    };

    /**
     * @brief Exception class for serializable-related errors.
     */
    class SerializableException : public Exception {
        public:
            SerializableException(const std::string& message) : Exception("SerializableException: " + message) {}
    };

    /**
     * @brief Exception class for serial string-related errors.
     */
    class SerialStringException : public Exception {
        public:
            SerialStringException(const std::string& message) : Exception("SerialStringException: " + message) {}
    };

    /**
     * @brief Exception class for socket-related errors.
     */
    class SocketException : public Exception {
        public:
            SocketException(const std::string& message) : Exception("SocketException: " + message) {}
    };
}
