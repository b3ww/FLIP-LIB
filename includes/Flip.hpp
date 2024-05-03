/*
** EPITECH PROJECT, 2023
** FLIP-LIB
** File description:
** Flip.hpp
*/

#pragma once

#include <functional>
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include "App.hpp"
#include "Serializable.hpp"

/**
 * @brief Macro to define a FLIP application
 *
 * This macro is used to define a FLIP application with a specified port and name.
 * It also creates an instance of the flip::App class for this application.
 *
 * @param appName The name of the application
 * @param port The port on which the application listens
 */
#define FLIP_APP(appName)                                                           \
    namespace __FLIP_secured {                                                      \
        namespace appName {                                                         \
            static flip::__FLIP_routeMap __routeMap;                                \
        }                                                                           \
    }                                                                               \
    static flip::App appName(#appName, __FLIP_secured::appName::__routeMap);

/**
 * @brief Macro to define a FLIP route
 *
 * This macro is used to define a FLIP route in a given application.
 * It also creates an initialization structure for this route, which registers the routing function in the route table.
 *
 * @param appName The name of the application to which the route belongs
 * @param routeName The name of the route
 * @param packType The type of packet used by the route
 */
#define FLIP_ROUTE(appName, routeName, packType)                                    \
    flip::__FLIP_routeReturnType routeName(const packType &);                       \
    struct __FLIP_##appName##routeName##_initializer {                              \
        static void initialize() {                                                  \
            __FLIP_secured::appName::__routeMap[#routeName] =                       \
            [](flip::serialStream __stream) -> flip::__FLIP_routeReturnType {       \
                packType __pack;                                                    \
                __pack.deserialize(__stream);                                       \
                return routeName(__pack);                                           \
            };                                                                      \
        }                                                                           \
        __FLIP_##appName##routeName##_initializer() { initialize(); }               \
    };                                                                              \
    static __FLIP_##appName##routeName##_initializer routeName##_init;              \
    flip::__FLIP_routeReturnType routeName(const packType &pack[[maybe_unused]])

/**
 * @brief Macro to declare a serializable type.
 *
 * This macro is used to declare a serializable.
 * It creates an initialization structure that registers the serializable type in the serializable types map.
 *
 * @param serializable The serializable type to be declared.
 */
#define FLIP_DECLARE_SERIALIZABLE_TEMPLATE(serializable)            \
    struct __FLIP_##serializable##_initializer {                    \
        static void initialize() {                                  \
            flip::__serializableTypes[#serializable] = []           \
                () -> std::unique_ptr<flip::Serializable> {         \
                    return std::make_unique<flip::serializable>();  \
            };                                                      \
        }                                                           \
        __FLIP_##serializable##_initializer() {initialize();}       \
    };                                                              \
    static __FLIP_##serializable##_initializer serializable##init;

/**
 * @brief Macro to define a FLIP response
 *
 * This macro is used to define a FLIP response with a specified code, response type, and response data.
 *
 * @param code The code of the response
 * @param respType The type of the response
 * @param respData The data of the response
 */
#define FLIP_RESPONSE(code, respType, respData)                             \
    respType resp(respData);                                                \
    return std::make_pair<uint16_t, flip::serialStream>(code, resp.serialize());

