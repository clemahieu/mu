#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
	class entry;
	class pipe;
	class routine
	{
	public:
		routine (boost::shared_ptr <lambda_p::errors::error_target> errors_a);
		routine (boost::shared_ptr <lambda_p::entry> input_a,	boost::shared_ptr <lambda_p::pipe> output_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a);
		boost::shared_ptr <lambda_p::entry> input;
		boost::shared_ptr <lambda_p::pipe> output;
		boost::shared_ptr <lambda_p::errors::error_target> errors;
	};
}

