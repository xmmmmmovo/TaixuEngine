//
// Created by xmmmmmovo on 2023/7/9.
//

#ifndef ENGINE_RUNTIME_RESOURCE_JSON_JSON_PARSER_HPP
#define ENGINE_RUNTIME_RESOURCE_JSON_JSON_PARSER_HPP

#include <filesystem>

#include <magic_enum.hpp>
#include <simdjson.h>

#include "common/base/macro.hpp"
#include "common/log/logger.hpp"
#include "resource/json/json_serializable.hpp"

namespace taixu {

template<typename T>
TX_INLINE void jsonDump(std::stringstream& strstream, T&& value) {
    auto const  member_size = refl::reflect(value).members.size;
    std::size_t cnt         = 0;

    // iterate over the members of T
    for_each(refl::reflect(value).members, [&](auto member) {
        // is_readable checks if the member is a non-const field
        // or a 0-arg const-qualified function marked with property attribute
        if constexpr (!is_readable(member)) { return; }

        // get_display_name prefers the friendly_name of the property over
        // the function name
        strstream << "\"" << get_display_name(member) << "\""
                  << ":";

        if constexpr (refl::descriptor::has_attribute<taixu::ISerializableStr>(member)) {

            strstream << "\"" << member(value) << "\"";
        } else if constexpr (refl::descriptor::has_attribute<taixu::ISerializableNumber>(member)) {

            strstream << member(value);
        } else if constexpr (refl::descriptor::has_attribute<taixu::ISerializableBool>(member)) {

            strstream << std::boolalpha << member(value);
        } else if constexpr (refl::descriptor::has_attribute<taixu::ISerializableNULL>(member)) {
            strstream << "null";
        } else if constexpr (refl::descriptor::has_attribute<taixu::ISerializableObject>(member)) {

            strstream << "{";
            jsonDump(strstream, member(value));
            strstream << "}";
        } else if constexpr (refl::descriptor::has_attribute<taixu::ISerializableList>(member)) {
            // TODO: check is this correct?
            strstream << "[";
            auto& member_ref = member(value);
            for (auto i = 0; i < member_ref.size(); i++) {
                jsonDump(strstream, member_ref[i]);
                if (i != member_ref.size() - 1) { strstream << ","; }
            }
            strstream << "]";
        } else {
            strstream << "\"" << member(value) << "\"";
        }
        if (++cnt != member_size) { strstream << ","; }
    });
}

template<typename T>
TX_INLINE tx_string dumpToJsonStr(T&& value) {
    std::stringstream strstream;
    strstream << "{";
    jsonDump(strstream, value);
    strstream << "}";
    return strstream.str();
}

template<typename T>
TX_INLINE bool dumpToJsonFile(T&& value, std::filesystem::path const& path) {
    // TODO: TODO
    return true;
}

template<typename T>
TX_INLINE void jsonLoad(simdjson::ondemand::document& json_object, T& value) {
    // iterate over the members of T
    for_each(refl::reflect(value).members, [&](auto member) {
        // is_readable checks if the member is a non-const field
        // or a 0-arg const-qualified function marked with property attribute
        if constexpr (!is_readable(member)) { return; }

        if constexpr (refl::descriptor::has_attribute<taixu::ISerializableStr>(member)) {
            member(value) = tx_string(json_object[get_display_name(member)].get_string().value());
        } else if constexpr (refl::descriptor::has_attribute<taixu::ISerializableNumber>(member)) {
            member(value) = json_object[get_display_name(member)].get_double();
        } else if constexpr (refl::descriptor::has_attribute<taixu::ISerializableBool>(member)) {
            member(value) = json_object[get_display_name(member)].get_bool();
        } else if constexpr (refl::descriptor::has_attribute<taixu::ISerializableObject>(member)) {
            simdjson::ondemand::object data = json_object[get_display_name(member)];
            member(value)                   = jsonLoad(data, member(value));
        } else if constexpr (refl::descriptor::has_attribute<taixu::ISerializableList>(member)) {
            simdjson::ondemand::array data       = json_object[get_display_name(member)];
            std::size_t               cnt        = data.count_elements();
            auto&                     member_ref = member(value);
            member_ref.resize(cnt);
            std::size_t idx = 0;
            for (auto sub_data : data) { member_ref[idx++] = jsonLoad(sub_data, member(value)); }
        } else if constexpr (refl::descriptor::has_attribute<taixu::ISerializableNULL>(member)) {
            throw std::runtime_error("not support null");
        } else {
            throw std::runtime_error("not support type");
        }
    });
}


/**
 * @brief
 * @tparam T
 * @param json_str `json`字符串，与iterate函数接受的参数类型相同
 * @return
 */
template<typename T>
TX_INLINE auto loadFromJsonStr(auto const& json_str) -> std::optional<T> {
    T                            value{};
    simdjson::ondemand::parser   parser;
    simdjson::ondemand::document json_object;
    auto const                   err = parser.iterate(json_str).get(json_object);
    if (err != simdjson::SUCCESS) {
        ERROR_LOG("Cannot parse json: {}", magic_enum::enum_name(err));
        return std::nullopt;
    }
    jsonLoad(json_object, value);
    return value;
}

/**
 * @brief load from json file
 * @tparam T
 * @param file_path
 * @return
 */
template<typename T>
TX_INLINE auto loadFromJsonFile(std::filesystem::path const& file_path) -> std::optional<T> {
    simdjson::padded_string json_str;
    if (auto const err = simdjson::padded_string::load(file_path.generic_string()).get(json_str);
        err != simdjson::SUCCESS) {
        ERROR_LOG("Cannot load json: {}, error: {}", file_path.filename().generic_string(),
                  magic_enum::enum_name(err));
        return std::nullopt;
    }
    return loadFromJsonStr<T>(json_str);
}

}// namespace taixu

#endif// ENGINE_RUNTIME_RESOURCE_JSON_JSON_PARSER_HPP
