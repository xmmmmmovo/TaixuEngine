//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_APPLICATION_HPP
#define TAIXUENGINE_APPLICATION_HPP

#include <memory>
#include <string_view>

// "" include headers
#include "core/base/public_singleton.hpp"
#include "engine.hpp"
#include "gui/window.hpp"

namespace taixu::editor {

/**
 * @brief Application for the whole editor
 *        use Singleton pattern
 */
class Application : public PublicSingleton<Application> {
    /*
      For User to use
    */
    friend class PublicSingleton<Application>;

private:
    /**
     * A window pointer, because our app only have one window,
     * so there is just one pointer
     * @see IWindow
     */
    std::unique_ptr<IWindow>       window_ptr{nullptr};
    std::unique_ptr<WindowContext> context_ptr{nullptr};
    // get engine instance raw pointer
    Engine                        *_engine_ptr = &Engine::getInstance();

    /**
     * @brief Main window width
     */
    static constexpr int32_t          MAIN_WINDOW_WIDTH  = 1366;
    /**
     * @brief Main window height
     */
    static constexpr int32_t          MAIN_WINDOW_HEIGHT = 768;
    /**
     * @brief Main window title
     */
    static constexpr std::string_view MAIN_WINDOW_TITLE  = "TaixuEngineEditor";

public:
    /**
     * @brief initWindow application
     */
    void initialize(std::vector<std::string_view> const &args);
    /**
     * @brief main run function
     */
    void run();
    /**
     * @brief destroyWindow function, to release memory.
     */
    void destroy();

private:
    /**
     * @brief initWindow application args
     */
    void initApplicationArgs(std::vector<std::string_view> const &args);
};

}// namespace taixu::editor

#endif//TAIXUENGINE_APPLICATION_HPP