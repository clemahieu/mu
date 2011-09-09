#pragma once

#include <lambda_p/parser/state.h>

namespace lambda_p
{	
	namespace parser
	{
		class begin : public state
		{
		public:
			begin(void);
			~begin(void);
			state_id state_type ();
		};
	}
}

