#pragma once

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class expression;
		}
		namespace parser
		{
			class target
			{
			public:
				virtual void operator () (mu::io::ast::expression * expression_a) = 0;
			};
		}
	}
}