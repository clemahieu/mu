#pragma once

#include <lambda_p/parser/declaration_location.h>

namespace lambda_p
{
	namespace parser
	{
		class data_target
		{
		public:
			virtual declaration_location sink_data () = 0;
		};
	}
}

