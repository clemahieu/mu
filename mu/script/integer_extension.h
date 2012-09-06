#pragma once

#include <mu/io/analyzer_state.h>
#include <mu/core/types.h>

namespace mu
{
    namespace core
    {
        namespace errors
        {
            class error_target;
        }
    }
    namespace io
    {
        namespace analyzer
        {
            class analyzer;
        }
    }
	namespace script
	{
		namespace integer
		{
			class node;
			class extension : public mu::io::analyzer::state
			{
			public:
                extension (mu::io::analyzer::analyzer & analyzer_a);
                void operator () (mu::io::tokens::token const & token_a) override;
                static bool const dominating = true;
                mu::io::analyzer::analyzer & analyzer;
			};
			mu::script::integer::node * core (mu::core::errors::error_target & errors_a, mu::string const & string);
			mu::script::integer::node * core_d (mu::core::errors::error_target & errors_a, std::wstring string_a);
			mu::script::integer::node * core (mu::core::errors::error_target & errors_a, std::wstring string_a, size_t base_a);
		}
	}
}
