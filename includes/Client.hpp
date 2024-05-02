/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Client.hpp
*/

#pragma once

#include "Serializable.hpp"
#include "Payload.hpp"
#include <limits>
#include <string>

namespace flip {
    class Client {
        private:
            std::string _ip;
            uint16_t _port;

        public:
            Client(const std::string &, const uint16_t &);
            template <typename T>
            void __makeRequest(const std::string &routeName, const T &serializable)
            {
                if (!std::is_base_of<Serializable, T>())
                    throw std::invalid_argument("Serializable must derided of flip::Serilaizable");
                std::unique_ptr<Serializable> serialStreamInterface = std::make_unique<Serializable>(serializable);
                Payload(routeName, 0, serialStreamInterface->serialize());
            }
            int request(const serialStream &);
    };
}