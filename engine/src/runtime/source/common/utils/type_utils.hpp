//
// Created by xmmmmmovo on 1/19/2024.
//

#pragma once

#include <array>
#include <type_traits>

namespace taixu {

template<typename T>
concept IsNumber = std::is_arithmetic_v<T>;

template<typename T>
concept IsIntegral = std::is_integral_v<T>;

template<typename T>
concept IsFloat = std::is_floating_point_v<T>;

template<typename T>
concept IsPointer = std::is_pointer_v<T>;

template<typename T>
concept IsReference = std::is_reference_v<T>;

template<typename Test, template<typename...> class Ref>
struct IsSpecialization : std::false_type {};

template<template<typename...> class Ref, typename... Args>
struct IsSpecialization<Ref<Args...>, Ref> : std::true_type {};

template<class T>
struct IsArray : std::is_array<T> {};
template<class T, std::size_t N>
struct IsArray<std::array<T, N>> : std::true_type {};

template<typename T>
concept IsFunction = std::is_function_v<T>;

template<typename T>
concept IsEnum = std::is_enum_v<T>;

template<typename T>
concept IsClass = std::is_class_v<T>;

template<typename T>
concept IsUnion = std::is_union_v<T>;

template<typename T>
using SameT = T;

/**
 * @brief iterable type
 *
 * @tparam T
 */
template<typename T>
concept IterableNotStrT =
        requires(T t) {
            { std::begin(t) } -> std::input_or_output_iterator;
            { std::end(t) } -> std::input_or_output_iterator;
        } &&
        !std::is_same_v<std::decay_t<T>, std::basic_string<typename T::value_type, typename T::traits_type,
                                                           typename T::allocator_type>>// Exclude std::string
        && !std::is_same_v<std::decay_t<T>, std::basic_string_view<typename T::value_type,
                                                                   typename T::traits_type>>// Exclude std::string_view
        && !std::is_same_v<std::decay_t<T>, const char*>                                    // Exclude const char*
        && !std::is_same_v<std::decay_t<T>, char*>                                          // Exclude char*
        && !std::is_array_v<std::decay_t<T>>;// Exclude char[] and other arrays;

// Concept to check if a container has key-value pairs (i.e., maps)
template<typename T>
concept KeyValueContainerT = requires(T t) {
    typename T::value_type;
    // Ensure that value_type is a pair (key-value pair)
    requires std::is_same_v<typename T::value_type, std::pair<const typename T::key_type, typename T::mapped_type>>;
};

}// namespace taixu
