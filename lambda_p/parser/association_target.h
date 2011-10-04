#pragma once

namespace lambda_p
{
	namespace core
	{
		class declaration;
		class node;
	}
	namespace parser
	{
		class association_target
		{
		public:
			virtual void sink_result (::lambda_p::core::declaration * declaration) = 0;
			virtual void sink_argument (::lambda_p::core::node * argument) = 0;
		};
	}
}

