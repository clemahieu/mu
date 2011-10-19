#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class statement;
		class routine;
	}
	namespace errors
	{
		class error;
	}
	namespace binder
	{
		class routine_instances;
	}
}
namespace lambda_p_kernel
{
	class routine;
	class routine_binder;
	class single_bind_routine
	{
	public:
		single_bind_routine (::boost::shared_ptr < lambda_p_kernel::routine> routine_a, ::boost::shared_ptr < lambda_p::binder::routine_instances> instances_a);
		void operator () (::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		::boost::shared_ptr < lambda_p::binder::routine_instances> outer_instances;
		::boost::shared_ptr < lambda_p_kernel::routine_binder> binder_m;
		::boost::shared_ptr < ::lambda_p::core::routine> outer_routine;
		::lambda_p::core::statement * statement;
	};
}