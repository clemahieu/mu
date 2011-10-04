#pragma once

namespace lambda_p
{
	namespace core
	{
		class data;
	}
	namespace parser
	{
		class data_target
		{
		public:
			virtual void sink_data (::lambda_p::core::data * data) = 0;
		};
	}
}

