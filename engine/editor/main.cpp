#include <array>
#include <cstdlib>
#include <string>

// render use
#include "argparse/argparse.hpp"
#include "engine.hpp"
#include "engine_args.hpp"
#include "gameplay/gui/window_context.hpp"
#include "ui/main_window/main_window.hpp"

/**
 * @brief initWindow spdlog config
 */
void initSpdlog() {
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);// Set global log level to debug
#else
    spdlog::set_level(spdlog::level::info);// Set global log level to info
#endif
}

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


int main(int argc, char *argv[]) {
    // avoid c-style array
    std::vector<std::string> const args(argv, argv + argc);

    initSpdlog();

    taixu::Engine *engine_ptr = &taixu::Engine::getInstance();
    engine_ptr->loadParams(args);

    spdlog::info("start init the application!");

    auto context_ptr = std::make_unique<taixu::WindowContext>(
            MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, MAIN_WINDOW_TITLE,
            createGraphicsAPILoader(taixu::EngineArgs::getInstance().api()),
            true);
    // init window pointer
    std::unique_ptr<taixu::editor::MainWindow> window_ptr_local =
            std::make_unique<taixu::editor::MainWindow>(context_ptr.get());
    // init window
    window_ptr_local->init();

    engine_ptr->init(std::move(context_ptr), std::move(window_ptr_local));

    spdlog::info("init the application finished!");

    engine_ptr->run();
    engine_ptr->destroy();

    return EXIT_SUCCESS;
}
