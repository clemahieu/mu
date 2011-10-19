#pragma once

#include <lambda_p/binder/instance.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
}
namespace lambda_p_kernel
{
	// Represents a routine that can be used as a node_instace
	class routine : public ::lambda_p::binder::instance
	{
	public:
		routine (::boost::shared_ptr < ::lambda_p::core::routine> routine_a);
		::boost::shared_ptr < ::lambda_p::core::routine> routine_m;
	};
}