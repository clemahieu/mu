#pragma once

#include <mu/io/analyzer/extensions/extension.h>

namespace mu
{
	namespace script
	{
		namespace integer
		{
			class node;
			class extension : public mu::io::analyzer::extensions::extension
			{
			public:
				void operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a) override;
			};
			mu::script::integer::node * core (mu::core::errors::error_target * errors_a, std::wstring & string);
			mu::script::integer::node * core_d (mu::core::errors::error_target * errors_a, wchar_t const * string_a);
			mu::script::integer::node * core (mu::core::errors::error_target * errors_a, wchar_t const * string_a, size_t base_a);
		}
	}
}
