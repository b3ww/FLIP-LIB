/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Request.hpp
*/

#pragma once

#include "Socket.hpp"
#include "Payload.hpp"
#include "Callback.hpp"

namespace flip {
    /**
     * @brief Request class representing a network request.
     *
     * This class represents a network request, encapsulating a payload and a callback manager.
     */
    class Request {
        private:
            const Payload _payload; ///< The payload associated with the request.
            CallbackManager _callbackManager; ///< The callback manager associated with the request.

        public:
            /**
             * @brief Deleted default constructor.
             *
             * This constructor is deleted to prevent instantiation of Request without payload and callback manager.
             */
            Request() = delete;

            /**
             * @brief Constructor for creating a Request with a specified payload and callback manager.
             *
             * @param payload The payload associated with the request.
             * @param callbackManager The callback manager associated with the request.
             */
            Request(const Payload& payload, CallbackManager& callbackManager);

            /**
             * @brief Gets the payload associated with the request.
             *
             * @return const Payload& The payload associated with the request.
             */
            const Payload& getPayload();

            /**
             * @brief Gets the payload associated with the request (const version).
             *
             * @return const Payload The payload associated with the request.
             */
            const Payload getPayload() const;

            /**
             * @brief Gets the callback manager associated with the request.
             *
             * @return const CallbackManager& The callback manager associated with the request.
             */
            const CallbackManager& getCallback();
    };
}
