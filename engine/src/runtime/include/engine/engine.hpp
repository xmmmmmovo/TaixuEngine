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

    PROTOTYPE_ONLY_GETTER_CONST(private, EngineContext, context);

private:
    /**
     * @brief engine clock
     */
    CpuClock _clock{};

public:
    void preInit(std::vector<std::string> const& args);
    void init(Window* window);
    /**
     * @brief This function only need call once before main loop
     */
    void start();
    void update();
    void destroy();
};

}// namespace taixu

#endif// ENGINE_H