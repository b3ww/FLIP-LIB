/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** MapPack.hpp
*/

#pragma once

#include "Serializable.hpp"
#include <unordered_map>
#include <memory>

namespace flip {
    class MapPack: public Serializable {
        public:
            MapPack() = default;
            MapPack(const serialStream &stream);
            serialStream serialize(void) const final {
                return {};
            }
            void deserialize(const serialStream &stream) final {
                (void)stream;
            }

            std::unordered_map<std::string, std::unique_ptr<Serializable>> &getMap(void);

            template <typename T>
            void set(const std::string &key, const T &serializable)
            {
                static_assert(std::is_base_of<Serializable, T>::value, "T must be derived from Serializable");
                _map[key] = std::move(std::make_unique<T>(serializable));
            }
        private:
            std::unordered_map<std::string, std::unique_ptr<Serializable>> _map;
    };

    #define FLIP_MAP(name) flip::MapPack name;
    #define FLIP_MAP_SET(mapName, key, serializableType, serializable) \
        mapName.set<serializableType>(key, serializable)
}
