#pragma once

#include <lambda_p/context.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	class node;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_script
{
	class operation;
	class context;
	class node;
	class call
	{
	public:
		call (size_t results_a, lambda_p::context context_a);
		lambda_p::context context;
		size_t results;
		std::vector <boost::shared_ptr <lambda_p_script::node>> arguments;
		void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::context & context);
		void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p_script::operation> operation_a, std::vector <boost::shared_ptr <lambda_p::node>> & arguments_a, lambda_p_script::context & context_a);
	};
}
