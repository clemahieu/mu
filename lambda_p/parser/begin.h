#pragma once

#include <lambda_p/parser/state.h>

namespace lambda_p
{	
	namespace parser
	{
		class begin : public state
		{
		public:
			state_id state_type ();
		};
	}
}

