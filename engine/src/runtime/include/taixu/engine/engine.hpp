/**
 * @file engine.hpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-10-20
 *
 * @copyright Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include <string>

#include "taixu/common/base/core.hpp"
#include "taixu/common/base/cpu_clock.hpp"
#include "taixu/common/designs/noncopyable.hpp"
#include "taixu/engine/engine_args.hpp"
#include "taixu/gameplay/gui/window.hpp"
#include "taixu/management/project/project.hpp"

TX_NAMESPACE_BEGIN

struct EnginePrivate;

class Engine final : public Noncopyable {
private:
    std::unique_ptr<EnginePrivate> _p;

    /**
     * @brief engine clock
     */
    CpuClock _clock{};

    /**
     * 保存engine的参数
     */
    EngineArgs _engine_args{};

public:
    Engine();

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
    void              changeEngineState(EngineState state);

    /// Project management
    bool                         loadProject(std::filesystem::path const& path);
    [[nodiscard]] Project const* getOpenedProject() const;

    /// Render management
    void enableImgui(std::function<void()>&& update_func);

    [[nodiscard]] EngineArgs const& getEngineArgs() const;
};

extern Engine g_engine;// NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

TX_NAMESPACE_END
