#pragma once

namespace lambda_p
{
	namespace parser
	{
		class data_target
		{
		public:
			virtual void sink_data (size_t * & data) = 0;
		};
	}
}

