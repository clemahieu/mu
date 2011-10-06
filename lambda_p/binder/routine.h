#pragma once

#include <lambda_p/binder/node_instance.h>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
	namespace binder
	{
		class routine : public ::lambda_p::binder::node_instance
		{
		public:
			routine (::lambda_p::core::routine * routine_a);
			::lambda_p::core::routine * routine_m;
		};
	}
}

