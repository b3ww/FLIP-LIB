/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Srting.cpp
*/

#include "SerialString.hpp"

namespace flip {
    SerialString::SerialString(const std::string& data) : _data(data)
    {
    }

    serialStream SerialString::serialize() const
    {
        return _data;
    }

    void SerialString::deserialize(const serialStream& stream)
    {
        _data = stream;
    }

    const std::string& SerialString::getData() const {
        return _data;
    }
}
