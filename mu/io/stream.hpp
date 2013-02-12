#pragma once

#include <cstring>

namespace mu
{
    namespace io
    {
        template <typename T>
        class stream
        {
        public:
            virtual void consume (size_t size_a) = 0;
            virtual T & operator [] (size_t size_a) = 0;
            virtual size_t size () = 0;
        };
    }
}