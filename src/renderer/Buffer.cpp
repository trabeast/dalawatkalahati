//
// Created by travisdev on 9/5/23.
//

#include "Buffer.h"

namespace DTK {
    Buffer::Buffer() : buffer(create()) {}
    Buffer::~Buffer() {}
    buffer_unit Buffer::create() {
        buffer_unit buffer;
        GL_CHECK(glGenBuffers(1, &buffer));
        return buffer;
    }
    void Buffer::bind() const {
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    }
    void Buffer::unbind() const {
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}// namespace DTK
