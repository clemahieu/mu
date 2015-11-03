#pragma once

#include <mu/core/types.hpp>

#include <array>

namespace mu
{
    namespace core
    {
        class string_hash
        {
        public:
            string_hash (mu::string const & string_a);
            string_hash (std::string const & string_a);
            std::array <uint8_t, 16> hash;
            mu::string text ();
        };        
    }
}