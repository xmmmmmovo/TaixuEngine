#include <fmt/format.h>

#include <taixu/engine/engine.hpp>

#include "ui/main_window/main_window.hpp"

/**
 * @brief Main window width
 */
static constexpr int32_t          MAIN_WINDOW_WIDTH  = 2560;
/**
 * @brief Main window height
 */
static constexpr int32_t          MAIN_WINDOW_HEIGHT = 1440;
/**
 * @brief Main window title
 */
static constexpr std::string_view MAIN_WINDOW_TITLE  = "TaixuEngineEditor";

int main(const int argc, char* argv[]) try {

    using namespace std::literals;
    using namespace taixu::editor;

    // avoid c-style array
    std::vector<std::string> const args(argv, argv + argc);

    taixu::g_engine.initRuntime(args);

    MainWindow main_window{{MAIN_WINDOW_TITLE.data(), MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT}};

    main_window.init();
    main_window.start();
    main_window.destroy();

    return EXIT_SUCCESS;
} catch (std::exception const& e_err) {
    std::cerr << "\n" << fmt::format("Error: {}\n", e_err.what());
    return 1;
} catch (...) {
    std::cerr << "\nUnknown error\n";
    return 1;
}
