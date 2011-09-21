#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace binder
	{
		class structure;
	}
}
namespace lambda_p_llvm
{
	class api
	{
	public:
		api (void);
		~api (void);
		::boost::shared_ptr < ::lambda_p::binder::structure> structure;
	};
}

