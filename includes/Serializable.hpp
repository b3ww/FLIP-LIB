/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Ipack.hpp
*/
#pragma once

#include <cstring>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include "Exceptions.hpp"


namespace flip {

    /**
     * @brief Alias for a serial stream.
     */
    typedef std::string serialStream;

    /**
     * @brief Abstract base class for serializable objects.
     */
    class Serializable {
        public:
            Serializable() = default;
            virtual ~Serializable() = default;
            /**
             * @brief Serialize the object to a serial stream.
             * @return The serialized data.
             */
            virtual serialStream serialize(void) const = 0;
            /**
             * @brief Deserialize the object from a serial stream.
             * @param stream The serial stream containing the data to deserialize.
             */
            virtual void deserialize(const serialStream& stream) = 0;
    };

    /**
     * @brief Map to store serializable types.
     */
    static std::unordered_map<std::string, std::function<std::unique_ptr<Serializable>(void)>> __serializableTypes;

    /**
     * @brief Template class for a typed serializable object.
     * @tparam T The type of the object.
     */
    template<typename T>
    class TypedSerializable : public Serializable {
        public:
            TypedSerializable() = default;
            TypedSerializable(const T& val) : value(val) {}

            /**
             * @brief Constructs a TypedSerializable object by deserializing data from a serial stream.
             * @param stream The serial stream containing the data.
             */
            TypedSerializable(const serialStream& stream)
            {
                deserialize(stream);
            }

            /**
             * @brief Serializes the object to a serial stream.
             * @return The serialized data.
             */
            serialStream serialize() const override
            {
                serialStream result(sizeof(T), '\0');
                const uint8_t* ptr = reinterpret_cast<const uint8_t*>(&value);
                std::copy(ptr, ptr + sizeof(T), result.begin());
                return result;
            }

            /**
             * @brief Deserializes data from a serial stream and sets the value of the object.
             * @param stream The serial stream containing the data.
             */
            void deserialize(const serialStream& stream) override
            {
                if (stream.size() != sizeof(T)) {
                    throw SerializableException("Invalid serial stream size");
                }
                const uint8_t* ptr = reinterpret_cast<const uint8_t*>(stream.data());
                std::memcpy(&value, ptr, sizeof(T));
            }

            T getValue() const { return value; }

        private:
            T value = T{};
    };

    /**
     * @brief Alias for a serializable object of type uint8_t.
     */
    typedef TypedSerializable<uint8_t> SerializableUint8;

    /**
     * @brief Alias for a serializable object of type uint16_t.
     */
    typedef TypedSerializable<uint16_t> SerializableUint16;

    /**
     * @brief Alias for a serializable object of type uint32_t.
     */
    typedef TypedSerializable<uint32_t> SerializableUint32;

    /**
     * @brief Alias for a serializable object of type uint64_t.
     */
    typedef TypedSerializable<uint64_t> SerializableUint64;

    /**
     * @brief Alias for a serializable object of type int8_t.
     */
    typedef TypedSerializable<int8_t> SerializableInt8;

    /**
     * @brief Alias for a serializable object of type int16_t.
     */
    typedef TypedSerializable<int16_t> SerializableInt16;

    /**
     * @brief Alias for a serializable object of type int32_t.
     */
    typedef TypedSerializable<int32_t> SerializableInt32;

    /**
     * @brief Alias for a serializable object of type int64_t.
     */
    typedef TypedSerializable<int64_t> SerializableInt64;

    /**
     * @brief Alias for a serializable object of type char.
     */
    typedef TypedSerializable<char> SerializableChar;

    /**
     * @brief Alias for a serializable object of type short.
     */
    typedef TypedSerializable<short> SerializableShort;

    /**
     * @brief Alias for a serializable object of type float.
     */
    typedef TypedSerializable<float> SerializableFloat;

    /**
     * @brief Alias for a serializable object of type double.
     */
    typedef TypedSerializable<double> SerializableDouble;

    /**
     * @brief Alias for a serializable object of type int.
     */
    typedef TypedSerializable<int> SerializableInt;
}
