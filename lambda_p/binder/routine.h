#pragma once

#include <lambda_p/binder/node_instance.h>

#include <boost/shared_ptr.hpp>

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
			routine (::boost::shared_ptr < ::lambda_p::core::routine> routine_a);
			::boost::shared_ptr < ::lambda_p::core::routine> routine_m;
		};
	}
}

