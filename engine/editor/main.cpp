#include <cstdlib>

// render use
#include "core/application.hpp"

int main() {
    decltype(auto) app = taixu::editor::Application::getInstance();
    app.initialize();
    app.run();
    app.destroy();
    return EXIT_SUCCESS;
}