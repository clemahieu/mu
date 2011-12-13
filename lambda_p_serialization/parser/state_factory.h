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
			virtual boost::shared_ptr <lambda_p::parser::state> create (lambda_p::parser::parser & parser_a, boost::shared_ptr <lambda_p::parser::state> previous_state) = 0;
		};
	}
}
