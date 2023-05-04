#include <array>
#include <cstdlib>
#include <string>

// render use
#include "application.hpp"

int main(int argc, char *argv[]) {
    // avoid c-style array
    std::vector<std::string> const args(argv, argv + argc);
    decltype(auto) app = taixu::editor::Application::getInstance();
    app.init(args);
    app.run();
    app.destroy();
    return EXIT_SUCCESS;
}
