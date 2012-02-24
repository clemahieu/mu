#pragma once

#include <mu/io/analyzer/extensions/extension.h>

namespace lambda_p_script
{
	namespace integer
	{
		class node;
		class extension : public mu::io::analyzer::extensions::extension
		{
		public:
			void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a) override;
		};
		boost::shared_ptr <lambda_p_script::integer::node> core (boost::shared_ptr <mu::core::errors::error_target> errors_a, std::wstring & string);
		boost::shared_ptr <lambda_p_script::integer::node> core_d (boost::shared_ptr <mu::core::errors::error_target> errors_a, wchar_t const * string_a);
		boost::shared_ptr <lambda_p_script::integer::node> core (boost::shared_ptr <mu::core::errors::error_target> errors_a, wchar_t const * string_a, size_t base_a);
	}
}

