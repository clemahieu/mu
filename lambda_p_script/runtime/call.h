#pragma once

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
	namespace runtime
	{
		class context;
		class node;
		class call
		{
		public:
			call (size_t results_a);
			size_t results;
			std::vector <boost::shared_ptr <lambda_p_script::runtime::node>> arguments;
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::runtime::context & context);
		};
	}
}
