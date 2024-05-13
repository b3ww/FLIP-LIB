/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-raytracer-alexandre.douard
** File description:
** SerialVector.hpp
*/

#pragma once

#include "Serializable.hpp"
#include <sstream>
#include <vector>

namespace flip {

    /**
     * @brief Class for serializing and deserializing vectors of serializable objects.
     *
     * @tparam T The type of elements stored in the vector.
     */
    template <typename T>
    class SerialVector : public Serializable {
        private:
            std::vector<T> _data;   /**< The vector of serializable objects. */
            char _delimiter;        /**< The delimiter used for serialization. */

        public:
            /**
             * @brief Default constructor.
             */
            SerialVector() = default;
            /**
             * @brief Constructor to initialize the vector and delimiter.
             *
             * @param data The vector of serializable objects.
             * @param delimiter The delimiter character for serialization (default is ':').
             */
            SerialVector(std::vector<T> data, char delimiter = ':'): _data(data), _delimiter(delimiter)
            {
                if (!std::is_base_of_v<Serializable, T>)
                    throw std::invalid_argument("T is not serializable");
            }

            /**
             * @brief Constructor to deserialize data from a serial stream.
             *
             * @param stream The serial stream containing the serialized data.
             * @param delimiter The delimiter character used for deserialization (default is ':').
             */
            SerialVector(const serialStream& stream, char delimiter = ':'): _data(0), _delimiter(delimiter)
            {
                if (!std::is_base_of_v<Serializable, T>)
                    throw std::invalid_argument("T is not serializable");
                deserialize(stream);
            }

            /**
             * @brief Serializes the vector.
             *
             * @return The serialized data as a serial stream.
             */
            serialStream serialize(void) const override
            {
                serialStream stream;

                for (size_t i = 0; i < _data.size(); i++) {
                    stream += _data[i].serialize(); // Append serialized data of each element to the stream
                    stream += i == (_data.size() - 1) ? ' ' : _delimiter; // Append delimiter after each element
                }
                return stream;
            }

            /**
             * @brief Deserializes the serial stream into the vector.
             *
             * @param stream The serial stream containing the serialized data.
             */
                void deserialize(const serialStream& stream) override
                {
                    _data.clear();
                    std::stringstream ss(stream);
                    std::string element;

                    while (std::getline(ss, element, _delimiter)) {
                        T e;
                        e.deserialize(element); // Deserialize each element individually
                        _data.push_back(e);
                    }
                }

            const std::vector<T> getData(void) const
            {
                return _data;
            }
    };
}
