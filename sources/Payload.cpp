/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Payload.cpp
*/

#include "Payload.hpp"
#include <string>
#include <iostream>

namespace flip {
    Payload::Payload(const serialStream &serialized)
    {
        deserialize(serialized);
    }

    Payload::Payload(const std::string &routeName, SerialUint16 code, const serialStream &serialized):
        _routeName(routeName), _code(code), _serialized(serialized)
    {
        if (routeName.length() > 64)
            throw std::invalid_argument("Route name must be <= 64");
    }

    Payload::Payload(const std::string &routeName, uint16_t code, const serialStream &serializedData):
        _routeName(routeName), _code(code), _serialized(serializedData)
    {
        if (routeName.length() > 64)
            throw std::invalid_argument("Route name must be <= 64");
    }

    serialStream Payload::serialize(void) const
    {
        std::string routeNameCopy = _routeName;
        routeNameCopy.resize(64, '\0');
        return routeNameCopy + _code.serialize() + _serialized;
    }

    void Payload::deserialize(const serialStream &serializable)
    {
        if (serializable.size() < 64)
            throw flip::PayloadException("Serializable canno't be convert to payload\
                abort request");
        _routeName = serializable.substr(0, 64);
        _code.deserialize(serializable.substr(64, 2));
        _serialized = serializable.substr(66);
    }

}
