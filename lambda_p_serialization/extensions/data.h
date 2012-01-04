#pragma once

#include <lambda_p_serialization/analyzer/extension.h>

namespace lambda_p_serialization
{
	namespace extensions
	{
		class data : public lambda_p_serialization::analyzer::extension
		{
		public:
			std::pair <size_t, std::vector <boost::shared_ptr <lambda_p::core::expression>>> operator () (std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> & values_a, size_t position_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a) override;
		};
	}
}

