#include "Logger.h"
#include "Renderer.h"

int main() {
    DTK::Logger::initialize();
    DTK_LOGGER_INFO("Hello, {}", "World!");
    DTK::Renderer::initialize();
    return 0;
}
