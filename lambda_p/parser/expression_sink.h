#pragma once

namespace lambda_p
{
	namespace core
	{
		class expression;
	}
	namespace parser
	{
		class expression_sink
		{
		public:
			virtual void sink (lambda_p::core::expression * expression) = 0;
		};
	}
}
