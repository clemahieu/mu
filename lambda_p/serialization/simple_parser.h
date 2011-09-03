#include <lambda_p/tokens/token.h>

namespace lambda_p
{
	namespace serialization
	{
		template <routine_sink>
		class simple_parser
		{
			simple_parser (routine_sink & target_a)
				: target (target_a)
			{
			}
			void operator () (::lambda_p::tokens::token * token)
			{

			}
			routine_sink & target;
		};
	}
}