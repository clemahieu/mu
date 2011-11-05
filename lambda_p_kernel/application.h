#pragma once

#include <lambda_p/binder/node.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace binder
	{
		class list;
	}
}
namespace lambda_p_kernel
{
	class routine;
	class application : public lambda_p::binder::node
	{
	public:
		application (boost::shared_ptr <lambda_p_kernel::routine> routine_a, boost::shared_ptr <lambda_p::binder::list> nodes_a);
		boost::shared_ptr <lambda_p_kernel::routine> routine;
		boost::shared_ptr <lambda_p::binder::list> nodes;
	};
}

