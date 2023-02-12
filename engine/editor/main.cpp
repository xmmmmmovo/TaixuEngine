#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

// render use
#include "core/application.hpp"

int main() {
    decltype(auto) app = taixu::editor::Application::getInstance();
    app.initialize();
    app.run();
    return EXIT_SUCCESS;
}
