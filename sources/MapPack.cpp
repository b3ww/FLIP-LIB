/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** MapPack.cpp
*/

#include "MapPack.hpp"

namespace flip {
    MapPack::MapPack(const serialStream &stream)
    {
        deserialize(stream);
    }

    std::unordered_map<std::string, std::unique_ptr<Serializable>> &MapPack::getMap(void)
    {
        return _map;
    }
}