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
            error_string (char32_t const * message_a, mu::core::error_type type_a, mu::core::region const & region_a = mu::empty_region);
            void output (std::ostream & out) override;
            mu::core::error_type type () override;
			mu::core::region region () override;
            mu::core::error_type type_m;
            mu::string message;
			mu::core::region region_m;
        };
    }
}