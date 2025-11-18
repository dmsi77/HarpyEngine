// buffer.hpp

#pragma once

#include "types.hpp"

namespace realware
{
    namespace utils
    {
        class cBuffer
        {
        public:
            explicit cBuffer() = default;
            ~cBuffer() = default;

        private:
            types::usize _byteSize = 0;
            void* _data = nullptr;
        };
    }
}