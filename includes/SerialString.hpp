/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** SerialSerialString.hpp
*/

#pragma once

#include "Serializable.hpp"

namespace flip {

    /**
     * @brief Class for serializing and deserializing strings.
     */
    class SerialString : public Serializable {
    private:
        std::string _data; /**< The string data */

    public:
        /**
         * @brief Default constructor.
         */
        SerialString() = default;

        /**
         * @brief Constructor initializing the string with given data.
         * @param data The string data.
         */
        SerialString(const std::string& data);

        /**
         * @brief Serialize the string data.
         * @return The serialized data.
         */
        serialStream serialize() const override;

        /**
         * @brief Deserialize the string data.
         * @param stream The serialized data.
         */
        void deserialize(const serialStream& stream) override;

        /**
         * @brief Get the string data.
         * @return The string data.
         */
        const std::string& getData() const;
    };

}
