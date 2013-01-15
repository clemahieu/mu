#pragma once

#include <mu/io/stream.hpp>

#include <boost/circular_buffer.hpp>

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
            boost::circular_buffer <char32_t> buffer;
            std::istream & stream;
        };
    }
}