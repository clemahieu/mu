#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
	class node;
}
namespace lambda_p_io
{
	namespace ast
	{
		class expression;
	}
	namespace analyzer
	{
		class extension
		{
		public:
			virtual void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & dependencies_a, lambda_p_io::ast::expression * expression_a, size_t position_a) = 0;
		};
	}
}

