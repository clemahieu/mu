#pragma once

namespace lambda_p_serialization
{
	namespace ast
	{
		class expression;
		class identifier;
		class visitor
		{
		public:
			virtual void operator () (lambda_p_serialization::ast::expression * expression_a) = 0;
			virtual void operator () (lambda_p_serialization::ast::identifier * identifier_a) = 0;
		};
	}
}

