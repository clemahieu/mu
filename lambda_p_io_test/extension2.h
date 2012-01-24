#pragma once

#include <lambda_p_io/analyzer/extensions/extension.h>

namespace lambda_p_io_test
{
	class extension2 : public lambda_p_io::analyzer::extensions::extension
	{
	public:
		void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a) override;
	};
}

