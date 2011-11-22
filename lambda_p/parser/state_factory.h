#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace parser
	{
		class state;
		class association_target;
		class parser;
		class routine;
		class state_factory
		{
		public:
			virtual boost::shared_ptr <lambda_p::parser::state> create (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::parser::association_target & target) = 0;
		};
	}
}
