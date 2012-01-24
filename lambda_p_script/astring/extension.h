#pragma once

#include <lambda_p_io/analyzer/extensions/extension.h>

namespace lambda_p_script
{
	namespace astring
	{
		class extension : public lambda_p_io::analyzer::extensions::extension
		{
		public:
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a) override;
		};
	}
}

