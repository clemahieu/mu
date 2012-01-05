#pragma once

#include <lambda_p/binder/node.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace binder
	{
		class list;
	}
	namespace core
	{
		class routine;
	}
}
namespace lambda_p_kernel
{
	class application : public lambda_p::binder::node
	{
	public:
		application (boost::shared_ptr <lambda_p::core::routine> routine_a, boost::shared_ptr <lambda_p::binder::list> nodes_a);
		boost::shared_ptr <lambda_p::core::routine> routine;
		boost::shared_ptr <lambda_p::binder::list> nodes;
	};
}

