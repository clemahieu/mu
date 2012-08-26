#pragma once

#include <mu/io/keywording_state.h>
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
        namespace keywording
        {
            class keywording;
        }
    }
	namespace script
	{
		namespace integer
		{
			class node;
			class extension : public mu::io::keywording::state
			{
			public:
                extension (mu::io::keywording::keywording & keywording_a);
                void operator () (mu::io::tokens::token * token_a) override;
                static bool const dominating = true;
                mu::io::keywording::keywording & keywording;
			};
			mu::script::integer::node * core (mu::core::errors::error_target & errors_a, mu::string & string);
			mu::script::integer::node * core_d (mu::core::errors::error_target & errors_a, std::wstring string_a);
			mu::script::integer::node * core (mu::core::errors::error_target & errors_a, std::wstring string_a, size_t base_a);
		}
	}
}
