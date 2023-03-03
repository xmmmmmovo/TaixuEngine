//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_APPLICATION_HPP
#define TAIXUENGINE_APPLICATION_HPP

#include <memory>

// "" include headers
#include "core/base/public_singleton.hpp"
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
    std::shared_ptr<IWindow> window{nullptr};

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
     * @brief init application
     */
    void initialize(int argc, char *argv[]);
    /**
     * @brief main run function
     */
    void run();
    /**
     * @brief destroy function, to release memory.
     */
    void destroy();

private:
    /**
     * @brief init application args
     * @param argc args count
     * @param argv args
     */
    void initApplicationArgs(int argc, char *argv[]);
};

}// namespace taixu::editor

#endif//TAIXUENGINE_APPLICATION_HPP
