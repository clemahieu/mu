#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace lambda_p
{
	namespace errors
	{
		class error;
	}
	namespace core
	{
		class entry;
		class pipe;
		class routine
		{
		public:
			routine (boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a);
			routine (boost::shared_ptr <lambda_p::core::entry> input_a,	boost::shared_ptr <lambda_p::core::pipe> output_a, boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a);
			boost::shared_ptr <lambda_p::core::entry> input;
			boost::shared_ptr <lambda_p::core::pipe> output;
			boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors;
		};
	}
}

