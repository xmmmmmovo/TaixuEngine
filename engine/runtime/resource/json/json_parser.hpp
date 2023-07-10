//
// Created by xmmmmmovo on 2023/7/9.
//

#ifndef ENGINE_RUNTIME_RESOURCE_JSON_JSON_PARSER_HPP
#define ENGINE_RUNTIME_RESOURCE_JSON_JSON_PARSER_HPP

#include <filesystem>
#include <iostream>
#include <string>

#include <refl.hpp>
#include <simdjson.h>

#include "core/base/macro.hpp"
#include "serializable.hpp"

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

        if constexpr (refl::descriptor::has_attribute<taixu::ISerializableStr>(
                              member)) {

            strstream << "\"" << member(value) << "\"";
        } else if constexpr (refl::descriptor::has_attribute<
                                     taixu::ISerializableNumber>(member)) {

            strstream << member(value);
        } else if constexpr (refl::descriptor::has_attribute<
                                     taixu::ISerializableBool>(member)) {

            strstream << std::boolalpha << member(value);
        } else if constexpr (refl::descriptor::has_attribute<
                                     taixu::ISerializableNULL>(member)) {
            strstream << "null";
        } else if constexpr (refl::descriptor::has_attribute<
                                     taixu::ISerializableObject>(member)) {

            strstream << "{";
            jsonDump(strstream, member(value));
            strstream << "}";
        } else if constexpr (refl::descriptor::has_attribute<
                                     taixu::ISerializableList>(member)) {
            // TODO: fix this
            strstream << "[";
            jsonDump(strstream, member(value));
            strstream << "]";
        } else {
            strstream << "\"" << member(value) << "\"";
        }
        if (++cnt != member_size) { strstream << ","; }
    });
}

template<typename T>
TX_INLINE std::string dumpToJson(T&& value) {
    std::stringstream strstream;
    strstream << "{";
    jsonDump(strstream, value);
    strstream << "}";
    return strstream.str();
}

template<typename T>
TX_INLINE void jsonLoad(simdjson::ondemand::document const& json_object,
                        T&                                  value) {


}

template<typename T>
TX_INLINE T loadFromJson(std::filesystem::path& file_path) {
    T                             value{};
    simdjson::ondemand::parser    parser;
    simdjson::padded_string const json_str =
            simdjson::padded_string::load(file_path.generic_string());
    simdjson::ondemand::document const json_object = parser.iterate(json_str);

    jsonLoad(json_object, value);

    return value;
}

}// namespace taixu

#endif// ENGINE_RUNTIME_RESOURCE_JSON_JSON_PARSER_HPP
