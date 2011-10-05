#pragma once

namespace lambda_p
{
	namespace binder
	{
		class data;
	}
	namespace parser
	{
		class data_target
		{
		public:
			virtual void sink_data (::lambda_p::binder::data * data) = 0;
		};
	}
}

