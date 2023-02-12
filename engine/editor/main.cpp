#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

// render use
#include "core/application.hpp"

const uint32_t WIDTH  = 1366;
const uint32_t HEIGHT = 768;

int main() {
    decltype(auto) app = taixu::editor::Application::getInstance();
    app.initialize();
    app.run();
    return EXIT_SUCCESS;
}
