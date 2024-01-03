#ifndef ENGINE_H
#define ENGINE_H

#include <common/base/macro.hpp>
#include <common/designs/public_singleton.hpp>

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

    EngineContext const& getContext() { return _context; }
};

}// namespace taixu

#endif// ENGINE_H