#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class expression;
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
		class unresolved
		{
		public:
			unresolved (lambda_p_io::ast::expression * expression_a, boost::shared_ptr <lambda_p::expression> result_a);
			void operator () (lambda_p_io::analyzer::routine & routine);
			lambda_p_io::ast::expression * expression;
			boost::shared_ptr <lambda_p::expression> result;
			size_t count;
			bool complete;
		};
	}
}

