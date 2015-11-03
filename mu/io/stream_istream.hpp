#pragma once

#include <mu/io/stream.hpp>

#include <deque>
#include <istream>

namespace mu
{
    namespace io
    {
        class stream_istream : public mu::io::stream <char32_t>
        {
        public:
            stream_istream (std::istream & stream_a, size_t size_a);
            void consume (size_t size_a) override;
            char32_t & operator [] (size_t size_a) override;
            size_t size () override;
        private:
            void refill ();
            std::deque <char32_t> buffer;
			size_t size_m;
            std::istream & stream;
        };
    }
}
