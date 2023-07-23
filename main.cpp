#include "src/logger/Logger.h"
#include "src/renderer/Renderer.h"

int main() {
    DTK::Logger::initialize();
    DTK::Logger::log(DTK::Logger::LEVEL::INFO, "Hello, World!");
    DTK::Renderer::initialize();
    return 0;
}
