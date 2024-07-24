//
// Created by xmmmmmovo on 1/19/2024.
//

#ifndef TYPE_UTILS_HPP_F632F579D1484A6BB335C3B82355AAB3
#define TYPE_UTILS_HPP_F632F579D1484A6BB335C3B82355AAB3

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

}// namespace taixu

#endif// TYPE_UTILS_HPP_F632F579D1484A6BB335C3B82355AAB3
