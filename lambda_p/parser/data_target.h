#pragma once

namespace lambda_p
{
	namespace core
	{
		class node;
	}
	namespace parser
	{
		class data_target
		{
		public:
			virtual void sink_data (::lambda_p::core::node * data) = 0;
		};
	}
}

