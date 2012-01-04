#pragma once

#include <utility>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
	namespace core
	{
		class expression;
	}
}
namespace lambda_p_io
{
	namespace ast
	{
		class node;
	}
	namespace analyzer
	{
		class expression;
		class extension
		{
		public:
			virtual std::pair <size_t, std::vector <boost::shared_ptr <lambda_p::core::expression>>> operator () (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> & values_a, size_t position_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a) = 0;
		};
	}
}

