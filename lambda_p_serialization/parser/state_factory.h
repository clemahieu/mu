#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p_serialization
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
			virtual boost::shared_ptr <lambda_p_serialization::parser::state> create (lambda_p_serialization::parser::parser & parser_a, boost::shared_ptr <lambda_p_serialization::parser::state> previous_state) = 0;
		};
	}
}
