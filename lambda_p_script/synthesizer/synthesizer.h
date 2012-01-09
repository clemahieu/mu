#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <map>

namespace lambda_p
{
	class routine;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_script
{
	namespace runtime
	{
		class routine;
	}
	namespace synthesizer
	{
		class synthesizer
		{
		public:
			synthesizer (boost::function <void (boost::shared_ptr <lambda_p_script::runtime::routine>)> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a);
			void operator () (boost::shared_ptr <lambda_p::routine> expression_a);
			boost::function <void (boost::shared_ptr <lambda_p_script::runtime::routine>)> target;	
			boost::shared_ptr <lambda_p::errors::error_target> errors;
		};
	}
}
