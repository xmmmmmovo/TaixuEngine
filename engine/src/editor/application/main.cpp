#include <array>
#include <cstdlib>
#include <string>

// render use
#include <engine/engine.hpp>
#include <engine/engine_args.hpp>

#include "ui/main_window/main_window.hpp"

/**
 * @brief Main window width
 */
static constexpr int32_t          MAIN_WINDOW_WIDTH  = 1920;
/**
 * @brief Main window height
 */
static constexpr int32_t          MAIN_WINDOW_HEIGHT = 1080;
/**
 * @brief Main window title
 */
static constexpr std::string_view MAIN_WINDOW_TITLE  = "TaixuEngineEditor";

auto main(int argc, char* argv[]) -> int {
    // avoid c-style array
    std::vector<std::string> const args(argv, argv + argc);

    taixu::editor::MainWindow main_window{
            MAIN_WINDOW_TITLE.data(), MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT};

    main_window.init(args);
    main_window.show();
    main_window.destroy();

    return EXIT_SUCCESS;
}
