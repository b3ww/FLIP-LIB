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
    class Request {
        private:
            const Payload _payload;
            CallbackManager _callbackManager;
        public:
            Request() = delete;
            Request(const Payload &, CallbackManager &);
            const Payload &getPayload(void);
            const Payload getPayload(void) const;
            const CallbackManager &getCallback(void);
    };
}
