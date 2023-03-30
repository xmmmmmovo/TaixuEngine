#include <array>
#include <cstdlib>

// render use
#include "application.hpp"

int main(int argc, char *argv[]) {
    // avoid c-style array
    std::vector<std::string_view> const args(argv, argv + argc);
    decltype(auto) app = taixu::editor::Application::getInstance();
    app.initialize(args);
    app.run();
    app.destroy();
    return EXIT_SUCCESS;
}
