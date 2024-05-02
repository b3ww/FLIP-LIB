/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Payload.hpp
*/

#pragma once

#include "Serializable.hpp"

namespace flip {
    class Payload: public Serializable {
        private:
            const std::string _routeName;
            SerializableUint16 _code;
            serialStream _serialized;
        public:
            Payload(const std::string &, SerializableUint16, serialStream);
            serialStream serialize(void) const final;
            void deserialize(const serialStream &) final;
    };
}
