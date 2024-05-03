/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Callback.cpp
*/

#include "Callback.hpp"

namespace flip {
    CallbackManager::CallbackManager(const std::unordered_map<uint16_t, __callback<serialStream>> &callbacks):
            _callbacks(callbacks)
    {
    }

    void CallbackManager::operator()(uint16_t code, const serialStream &serialized) const
    {
        if (code == 42) {
            __FLIP_default_callback_error_42(code, serialized);
            return;
        }
        for (const auto &pair: _callbacks) {
            if (pair.first == code) {
                pair.second(code, serialized);
                return;
            }
        }
        _default(code, serialized);
    }
}
