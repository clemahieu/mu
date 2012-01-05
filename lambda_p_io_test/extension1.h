#pragma once

#include <lambda_p_io/analyzer/extension.h>

namespace lambda_p_io_test
{
	class extension1 : public lambda_p_io::analyzer::extension
	{
	public:
		void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & dependencies_a, lambda_p_io::ast::expression * expression_a, size_t position_a) override;
	};
}

