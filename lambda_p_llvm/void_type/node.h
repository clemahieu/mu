#pragma once

#include <lambda_p_llvm/type/node.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p_llvm
{
	namespace context
	{
		class node;
	}
	namespace void_type
	{
		class node : public lambda_p_llvm::type::node
		{
		public:
			node (boost::shared_ptr <lambda_p_llvm::context::node> context_a);
			llvm::Type * type () override;
			llvm::Type * type_m;
		};
	}
}

