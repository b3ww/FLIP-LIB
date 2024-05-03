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

namespace flip {
    /**
     * @brief Alias for callback function signature.
     */
    template <typename T>
    using __callback = std::function<void(uint16_t code, const T &)>;

    /**
     * @brief Represents a callback function.
     */
    template <typename T>
    class Callback {
        private:
            __callback<T> _callback; ///< The callback function.

        public:
            /**
             * @brief Deleted default constructor.
             */
            Callback() = delete;

            /**
             * @brief Constructs a Callback object with a callback function.
             * @param f The callback function.
             */
            Callback(const __callback<T> &f):
                _callback(f)
            {
                if (!std::is_base_of_v<Serializable, T>)
                    throw std::invalid_argument("T is not serializable");
            }

            /**
             * @brief Invokes the callback function.
             * @param code The code.
             * @param serialized The serialized data.
             */
            void operator()(uint16_t code, const T &serialized)
            {
                _callback(code, serialized);
            }
    };

    /**
     * @brief Default callback for route not found.
     */
    static __callback<serialStream> __FLIP_default_callback = (
        [](uint16_t code, const serialStream &_[[maybe_unused]]) -> void {
            std::cout << "Callback not found for code: " << code  << std::endl;
        }
    );

    /**
     * @brief Default callback for route execution errors.
     */
    static __callback<serialStream> __FLIP_default_callback_error_42 = (
        [](uint16_t [[maybe_unused]], const serialStream &exception) -> void {
            std::cout << "Route execution terminated by an exception: "
                      << exception << std::endl;
        }
    );

    /**
     * @brief Manages callback functions.
     */
    class CallbackManager {
    private:
        std::unordered_map<uint16_t, __callback<serialStream>> _callbacks; ///< The map of callbacks.
        __callback<serialStream> _default = __FLIP_default_callback; ///< The default callback.

    public:
        /**
         * @brief Constructs a CallbackManager object with a map of callbacks.
         * @param callbacks The map of callbacks.
         */
        CallbackManager(const std::unordered_map<uint16_t, __callback<serialStream>> &callbacks);

        /**
         * @brief Invokes the appropriate callback function.
         * @param code The code.
         * @param serialized The serialized data.
         */
        void operator()(uint16_t code, const serialStream &serialized) const;
    };

    /**
     * @brief Creates a callback function with a specified code and callback.
     * @tparam T The type of the callback.
     * @param code The code.
     * @param callback The callback function.
     * @return The created callback.
     */
    template <typename T>
    std::pair<uint16_t, __callback<serialStream>> makeCallback(uint16_t code, __callback<T> callback)
    {
        if (!std::is_base_of_v<Serializable, T>)
            throw std::invalid_argument("T is not serializable");
        return {
            code, [callback](uint16_t code, const serialStream &serialized) -> void {
                T deserialized;
                deserialized.deserialize(serialized);
                callback(code, deserialized);
            }
        };
    }
}
