#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class set;
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
		class set
		{
		public:
			set (lambda_p_io::analyzer::routine & routine_a, lambda_p_io::ast::expression * expression_a);
			boost::shared_ptr <lambda_p::set> result;
		};
	}
}

