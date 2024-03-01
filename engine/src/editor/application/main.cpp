#include "ui/common/editor_context.hpp"
#include <cstdlib>

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

int main(const int argc, char* argv[]) try {

    using namespace std::literals;
    using namespace taixu::editor;

    // avoid c-style array
    std::vector<std::string> args(argv, argv + argc);

    static constexpr auto EDITOR_ARG = "--editor"sv;
    args.emplace_back(EDITOR_ARG);

    g_editor_context.engine_ptr = &taixu::g_engine;

    MainWindow main_window{
            {MAIN_WINDOW_TITLE.data(), MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT}};

    main_window.init(args);
    main_window.start();
    main_window.destroy();

    return EXIT_SUCCESS;
} catch (std::exception const& e_err) {
    std::fprintf(stderr, "\n");
    std::fprintf(stderr, "Error: %s\n", e_err.what());
    return 1;
}
