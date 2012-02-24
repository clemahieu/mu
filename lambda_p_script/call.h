#pragma once

#include <core/context.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace mu
{
	namespace core
	{
		class node;
		namespace errors
		{
			class error_target;
		}
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
		call (size_t results_a, mu::core::context context_a);
		mu::core::context context;
		size_t results;
		std::vector <boost::shared_ptr <lambda_p_script::node>> arguments;
		void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, lambda_p_script::context & context);
		void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <lambda_p_script::operation> operation_a, std::vector <boost::shared_ptr <mu::core::node>> & arguments_a, lambda_p_script::context & context_a);
	};
}
