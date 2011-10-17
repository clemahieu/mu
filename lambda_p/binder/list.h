#pragma once

#include <lambda_p/binder/instance.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace binder
	{
		class instance;
		class list : public ::lambda_p::binder::instance
		{
		public:
			::std::vector < ::boost::shared_ptr < ::lambda_p::binder::instance> > instances;
		};
	}
}

