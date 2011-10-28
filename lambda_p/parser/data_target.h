#pragma once

#include <boost/function.hpp>

namespace lambda_p
{
	namespace parser
	{
		class data_target
		{
		public:
			virtual boost::function <void (size_t)> sink_data () = 0;
		};
	}
}

