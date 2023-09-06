//
// Created by travisdev on 9/5/23.
//

#include "Buffer.h"

namespace DTK {
    Buffer::Buffer() : buffer(create()) {}
    Buffer::~Buffer() = default;
    buffer_unit Buffer::create() {
        buffer_unit buffer;
        GL_CHECK(glGenBuffers(1, &buffer));
        return buffer;
    }
    void Buffer::bind() const {
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void Buffer::unbind() const {
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void Buffer::initializeData(const void *data, size_t size) const {
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }
}// namespace DTK
