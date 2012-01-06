#pragma once

namespace lambda_p_io
{
	namespace ast
	{
		class expression;
		class parameters;
		class identifier;
		class visitor
		{
		public:
			virtual void operator () (lambda_p_io::ast::parameters * parameters_a) = 0;
			virtual void operator () (lambda_p_io::ast::expression * expression_a) = 0;
			virtual void operator () (lambda_p_io::ast::identifier * identifier_a) = 0;
		};
	}
}

