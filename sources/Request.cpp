/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Request.cpp
*/

#include "Request.hpp"

namespace flip {
    Request::Request(const Payload &payload, CallbackManager &callbackManager):
        _payload(payload), _callbackManager(callbackManager)
    {
    }

    const Payload &Request::getPayload(void)
    {
        return _payload;
    }

    const Payload Request::getPayload(void) const
    {
        return _payload;
    }

    const CallbackManager &Request::getCallback(void)
    {
        return _callbackManager;
    }
}