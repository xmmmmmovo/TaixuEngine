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

template<typename I, typename T = IJsonable<I>>
std::string dumpJsonString(T const& jsonObj);
std::string dumpJsonFile(std::ifstream const& stream);

template<typename I, typename T = IJsonable<I>>
I loadJsonString(std::string jsonStr);
template<typename I, typename T = IJsonable<I>>
I loadJsonFile(std::ofstream const& stream);
}// namespace taixu

#include "json_parser.inc"
#endif//TAIXUENGINE_JSON_PARSER_HPP
