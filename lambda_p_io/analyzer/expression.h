#pragma once

#include <lambda_p_io/ast/visitor.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class expression;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_io
{
	namespace analyzer
	{
		class routine;
		class resolver;
		class expression : public lambda_p_io::ast::visitor
		{
		public:
			expression (lambda_p_io::analyzer::routine & routine_a, lambda_p_io::ast::expression * expression_a);
			void operator () (lambda_p_io::ast::expression * expression_a) override;
			void operator () (lambda_p_io::ast::identifier * identifier_a) override;
			lambda_p_io::analyzer::routine & routine;
			lambda_p_io::ast::expression * expression_m;
			boost::shared_ptr <lambda_p_io::analyzer::resolver> resolver;
			boost::shared_ptr <lambda_p::expression> result;
		};
	}
}

