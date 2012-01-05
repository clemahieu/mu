#pragma once

namespace lambda_p_io
{
	namespace analyzer
	{
		class expression;
		class extension
		{
		public:
			virtual void operator () (lambda_p_io::analyzer::expression & expression_a) = 0;
		};
	}
}

