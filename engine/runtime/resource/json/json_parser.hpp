//
// Created by xmmmmmovo on 2023/2/26.
//

#ifndef TAIXUENGINE_JSON_PARSER_HPP
#define TAIXUENGINE_JSON_PARSER_HPP


#include <fstream>
#include <nlohmann/json.hpp>

#include "jsonable.hpp"

namespace taixu {

using json = nlohmann::json;

// template<typename I, typename T = IJsonable<I>>
// std::string dumpJsonString(T const& jsonObj);
// std::string dumpJsonFile(std::ifstream const& stream);

// template<typename I, typename T = IJsonable<I>>
// I loadJsonString(std::string jsonStr);
// template<typename I, typename T = IJsonable<I>>
// I loadJsonFile(std::ofstream const& stream);


// 
template<typename T>
json serialize(const T& obj) {
    json j;
    static_assert(std::is_base_of<IJsonable, T>::value, "T must be a subclass of Reflector");
    const IJsonable& reflector = static_cast<const IJsonable&>(obj);
    j = toJson(reflector);
    return j;
}

// 
template<typename T>
void deserialize(const std::string& json_str, T& obj) {
    json j = json::parse(json_str);
    static_assert(std::is_base_of<IJsonable, T>::value, "T must be a subclass of Reflector");
    IJsonable& reflector = static_cast<IJsonable&>(obj);
    reflector.fromJson(j);
}

}// namespace taixu

#include "json_parser.inc"
#endif//TAIXUENGINE_JSON_PARSER_HPP
