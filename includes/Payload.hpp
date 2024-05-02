/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Payload.hpp
*/

#pragma once

#include "Serializable.hpp"

namespace flip {
    /**
     * @brief Class representing the payload transmitted in network requests.
     *
     * This class inherits from Serializable to enable serialization and transmission over the network.
     */
    class Payload: public Serializable {
        private:
            std::string _routeName; /**< The name of the route */
            SerializableUint16 _code; /**< The code associated with the payload */
            serialStream _serialized; /**< The serialized data */

        public:
            /**
             * @brief Constructor taking serialized data as input.
             * @param serializedData The serialized data representing the payload.
             */
            Payload(const serialStream &serializedData);

            /**
             * @brief Constructor taking route name, code, and serialized data as inputs.
             * @param routeName The name of the route.
             * @param code The code associated with the payload.
             * @param serializedData The serialized data representing the payload.
             */
            Payload(const std::string &routeName, SerializableUint16 code, const serialStream &serializedData);

            /**
             * @brief Serialize the payload.
             * @return The serialized data.
             */
            serialStream serialize(void) const final;

            /**
             * @brief Deserialize the payload.
             * @param stream The serialized data representing the payload.
             */
            void deserialize(const serialStream &stream) final;
    };
}