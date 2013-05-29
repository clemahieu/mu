#pragma once

#include <mu/core/types.hpp>

namespace mu
{
    namespace core
    {
        class string_hash
        {
        public:
            string_hash (mu::string const & string_a);
            string_hash (std::string const & string_a);
            uint8_t hash [16];
            mu::string text ();
        };        
    }
}