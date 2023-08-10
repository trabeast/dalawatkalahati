#include "Logger.h"
#include "Renderer.h"

int main() {
    DTK::Logger::initialize();
    DTK::Renderer::initialize();
    return 0;
}
