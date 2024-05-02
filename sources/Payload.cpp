/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Payload.cpp
*/

#include "Payload.hpp"
#include <string>

namespace flip {
    Payload::Payload(const std::string &routeName, SerializableUint16 code, serialStream serialized):
        _routeName(routeName), _code(code), _serialized(serialized)
    {
        if (routeName.length() > 64)
            throw std::invalid_argument("Route name must be <= 64");
    }

    serialStream Payload::serialize(void) const
    {
        return _routeName + _code.serialize() + _serialized;
    }

    void Payload::deserialize(const serialStream &)
    {

    }

}
