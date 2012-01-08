#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class call;
}
namespace lambda_p_script
{
	namespace synthesizer
	{
		class routine;
		class order
		{
		public:
			order (lambda_p_script::synthesizer::routine & routine_a, boost::shared_ptr <lambda_p::call> call_a);
			void operator () ();
			lambda_p_script::synthesizer::routine & routine;
			boost::shared_ptr <lambda_p::call> call;
		};
	}
}

