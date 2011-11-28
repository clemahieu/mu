#pragma once

#include <lambda_p/parser/state_factory.h>

namespace lambda_p_kernel
{
	namespace parser_factories
	{
		class number : public lambda_p::parser::state_factory
		{
		public:
			boost::shared_ptr <lambda_p::parser::state> create (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::parser::association_target & target) override;
		};	
	}
}
