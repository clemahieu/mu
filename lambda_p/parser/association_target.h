#pragma once

#include <lambda_p/parser/declaration_location.h>

namespace lambda_p
{
	namespace parser
	{
		class association_target
		{
		public:
			virtual declaration_location sink_declaration () = 0;
			virtual declaration_location sink_argument () = 0;
		};
	}
}

