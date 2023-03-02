#include <cstdlib>

// render use
#include "application.hpp"

int main(int argc, char *argv[]) {
    decltype(auto) app = taixu::editor::Application::getInstance();
    app.initialize(argc, argv);
    app.run();
    app.destroy();
    return EXIT_SUCCESS;
}
