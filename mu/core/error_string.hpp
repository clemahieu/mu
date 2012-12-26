#pragma once

#include <mu/core/types.hpp>
#include <mu/core/error.hpp>

#include <string>

namespace mu
{
    namespace core
    {
        class error_string : public mu::core::error
        {
        public:
            error_string (char32_t const * message_a);
            mu::string message;
        };
    }
}