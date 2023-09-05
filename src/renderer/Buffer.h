//
// Created by travisdev on 9/5/23.
//

#pragma once

#include "LogChecker.h"
namespace DTK {

    using buffer_unit = unsigned int;

    class Buffer : protected LogChecker {
    public:
        explicit Buffer();
        virtual ~Buffer();

        void bind() const;
        void unbind() const;

        const buffer_unit buffer;

    private:
        static buffer_unit create();
    };

}// namespace DTK
