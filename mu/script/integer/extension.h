#pragma once

#include <mu/io/analyzer/extensions/extension.h>
#include <mu/core/types.h>

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
                bool operator () () override;
				void operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a, mu::string remaining) override;
			};
			mu::script::integer::node * core (mu::core::errors::error_target * errors_a, mu::string & string);
			mu::script::integer::node * core_d (mu::core::errors::error_target * errors_a, std::wstring string_a);
			mu::script::integer::node * core (mu::core::errors::error_target * errors_a, std::wstring string_a, size_t base_a);
		}
	}
}
