#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace parser
	{
		class state;
		class state_factory
		{
		public:
			virtual boost::shared_ptr <lambda_p::parser::state> create () = 0;
		};
	}
}
