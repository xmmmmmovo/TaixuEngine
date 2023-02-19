//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_APPLICATION_HPP
#define TAIXUENGINE_APPLICATION_HPP

#include <memory>

// "" include headers
#include "application_context.hpp"
#include "gui/window.hpp"

namespace taixu::editor {

/**
 * @brief Application for the whole editor
 *        Singleton pattern
 */
class Application {
private:
    Application()  = default;
    ~Application() = default;

public:
    Application(const Application &)            = delete;
    Application &operator=(const Application &) = delete;

    static Application &getInstance() {
        // thread safe create instance
        static Application instance;
        return instance;
    }

    /*
 *    For User to use
 * */
private:
    std::shared_ptr<gui::IWindow>       window{nullptr};
    std::shared_ptr<ApplicationContext> context{};

    static constexpr int32_t          MAIN_WINDOW_WIDTH  = 1366;
    static constexpr int32_t          MAIN_WINDOW_HEIGHT = 768;
    static constexpr std::string_view MAIN_WINDOW_TITLE  = "TaixuEngineEditor";

public:
    void initialize();
    void run();
    void destroy();

    std::shared_ptr<ApplicationContext> getContext();
};

}// namespace taixu::editor

#endif//TAIXUENGINE_APPLICATION_HPP
