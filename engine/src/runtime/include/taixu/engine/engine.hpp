
#pragma once

#include <string>

#include "taixu/common/base/core.hpp"
#include "taixu/common/designs/noncopyable.hpp"
#include "taixu/engine/engine_args.hpp"
#include "taixu/gameplay/gui/window.hpp"

namespace taixu {

class Engine final : public Noncopyable {
private:
public:
    /**
     * 在最开始传递参数化表的初始化，用于初始化比如Logger之类的
     * @param args 初始化参数表
     */
    void initRuntime(std::vector<std::string> const& args);
    /**
     * 用于初始化渲染器和资源管理器等
     * @param window
     */
    void initWithWindow(Window* window);

    /**
     * @brief This function only need call once before main loop
     */
    void beforeStart();
    void update();
    void destroy() const;

    EngineArgs const& getArgs();

    void changeEngineState(EngineState state);

    bool                         loadProject(std::filesystem::path const& path);
    [[nodiscard]] Project const* getOpenedProject() const;
};

extern Engine g_engine;// NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

}// namespace taixu
