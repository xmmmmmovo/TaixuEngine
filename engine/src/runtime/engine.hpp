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
private:
    EngineContext _context;

public:
    void init(const std::vector<std::string>& args);
    void update();
    void destroy();
};

}// namespace taixu

#endif// ENGINE_H