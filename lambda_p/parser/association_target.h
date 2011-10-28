#pragma once

#include <boost/function.hpp>

namespace lambda_p
{
	namespace parser
	{
		class association_target
		{
		public:
			virtual boost::function <void (size_t)> sink_declaration () = 0;
			virtual boost::function <void (size_t)> sink_argument () = 0;
		};
	}
}

