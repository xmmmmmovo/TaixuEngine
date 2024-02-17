
#pragma once

#include "common/base/cpu_clock.hpp"
#include "common/designs/public_singleton.hpp"
#include "engine_context.hpp"

#include <string>


namespace taixu {

class Engine final : public PublicSingleton<Engine> {
    friend class PublicSingleton;

private:
    /**
     * @brief engine clock
     */
    CpuClock _clock{};

public:
    void preInit();
    void init(std::vector<std::string> const& args, Window* window);
    /**
     * @brief This function only need call once before main loop
     */
    void beforeStart();
    void update();
    void destroy();
};

}// namespace taixu
