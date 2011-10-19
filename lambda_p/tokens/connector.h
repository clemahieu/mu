#pragma once

#include <lambda_p/tokens/token.h>

namespace lambda_p
{
	namespace tokens
	{
		class connector : public lambda_p::tokens::token
		{
		public:
			connector(void);
			~connector(void);
			token_ids token_id ();
		};
	}
}

