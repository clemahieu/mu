#pragma once

#include <lambda_p/parser/state.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace parser
	{
		class routine;
		class data_target;
		class data : public state
		{
		public:
			data (boost::shared_ptr <lambda_p::parser::routine> routine_a, boost::shared_ptr <lambda_p::parser::data_target> target_a);
			state_id state_type ();
			boost::shared_ptr <lambda_p::parser::routine> routine;
			boost::shared_ptr <lambda_p::parser::data_target> target;
		};
	}
}

