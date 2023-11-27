#ifndef ENGINE_H
#define ENGINE_H

#include <base/macro.hpp>
#include <designs/public_singleton.hpp>

#include <filesystem>
#include <memory>

#include "engine_context.hpp"

namespace taixu {

class Engine final : public PublicSingleton<Engine> {
    friend class PublicSingleton<Engine>;

public:
    static void parseParams(const std::vector<std::string>& args);

    void init();
    void update();
    void destroy();
};

}// namespace taixu

#endif// ENGINE_H