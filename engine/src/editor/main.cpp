#include <array>
#include <cstdlib>
#include <string>

// render use
#include <runtime/engine.hpp>
#include <runtime/engine_args.hpp>

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

int main(int argc, char* argv[]) {
    // avoid c-style array
    std::vector<std::string> const args(argv, argv + argc);


    return EXIT_SUCCESS;
}
