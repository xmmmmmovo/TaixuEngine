//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_APPLICATION_HPP
#define TAIXUENGINE_APPLICATION_HPP

#include <memory>
#include <string>
#include <string_view>

// "" include headers
#include "core/base/public_singleton.hpp"
#include "engine.hpp"
#include "gameplay/gui/window.hpp"

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
    std::unique_ptr<IWindow>       _window_ptr{nullptr};
    std::unique_ptr<WindowContext> _context_ptr{nullptr};
    /**
     * @brief Engine raw pointer
     */
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
    void initialize(std::vector<std::string> const &args);
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
    static void initApplicationArgs(std::vector<std::string> const &args);
};

}// namespace taixu::editor

#endif//TAIXUENGINE_APPLICATION_HPP
