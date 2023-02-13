#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>
#include <cmath>

// render use
#include "core/application.h"

int main() {
    decltype(auto) app = taixu::editor::Application::getInstance();
    app.initialize();
    app.run();
    return EXIT_SUCCESS;
}
