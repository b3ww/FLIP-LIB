/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Callback.hpp
*/

#pragma once

#include <functional>
#include <unordered_map>
#include "Payload.hpp"
#include "Serializable.hpp"

namespace flip {
    template <typename T>
    using __callback = std::function<void(uint16_t code, const T &)>;

    template <typename T>
    class Callback {
        private:
            __callback<T> _callback;
        public:
            Callback() = delete;

            Callback(const __callback<T> &f):
                _callback(f)
            {
                if (!std::is_base_of_v<Serializable, T>)
                    throw std::invalid_argument("T is not serializable");
            }

            virtual void operator()(uint16_t code, const T &seralized)
            {
                _callback(code, seralized);
            }
    };

    class CallbackManager {
        private:
            std::unordered_map<uint16_t, __callback<serialStream>> _callbacks;

        public:
            CallbackManager(const std::unordered_map<uint16_t, __callback<serialStream>> &callbacks):
                _callbacks(callbacks)
            {
            }
    };

    template <typename T>
    std::pair<uint16_t, __callback<serialStream>> makeCallback(uint16_t code, __callback<T> callback)
    {
        if (!std::is_base_of_v<Serializable, T>)
            throw std::invalid_argument("T is not serializable");
        return {
            code, [callback](uint16_t code, const serialStream &serialized) -> void {
                T deserilaized;
                deserilaized.deserialize(serialized);
                callback(code, deserilaized);
            }
        };
    }
}