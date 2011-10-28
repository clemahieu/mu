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
		class error_list;
	}
	namespace binder
	{
		class node_list;
	}
}
namespace lambda_p_kernel
{
	class routine;
	class apply;
	class single_bind_routine
	{
	public:
		single_bind_routine (boost::shared_ptr <lambda_p_kernel::routine> routine_a, boost::shared_ptr <lambda_p::binder::node_list> nodes_a);
		void operator () (lambda_p::errors::error_list & problems);
		boost::shared_ptr <lambda_p::binder::node_list> outer_nodes;
		boost::shared_ptr <lambda_p_kernel::apply> binder_m;
		boost::shared_ptr <lambda_p::core::routine> outer_routine;
		lambda_p::core::statement * statement;
	};
}