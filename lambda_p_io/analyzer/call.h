#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class call;
}
namespace lambda_p_io
{
	namespace ast
	{
		class expression;
	}
	namespace analyzer
	{
		class routine;
		class call
		{
		public:
			call (lambda_p_io::analyzer::routine & routine_a, lambda_p_io::ast::expression * expression_a);
			boost::shared_ptr <lambda_p::call> result;
		};
	}
}

