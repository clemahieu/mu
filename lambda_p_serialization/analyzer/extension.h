#pragma once

namespace lambda_p_serialization
{
	namespace analyzer
	{
		class expression;
		class extension
		{
		public:
			virtual void operator () (lambda_p_serialization::analyzer::expression * expression) = 0;
		};
	}
}

