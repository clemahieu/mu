#pragma once

#include <lambda_p_llvm/type/node.h>

#include <boost/shared_ptr.hpp>

namespace llvm
{
	class PointerType;
}
namespace lambda_p_llvm
{
	namespace context
	{
		class node;
	}
	namespace pointer_type
	{
		class node : public lambda_p_llvm::type::node
		{
		public:
			node (boost::shared_ptr <lambda_p_llvm::context::node> context_a, llvm::PointerType * pointer_type_a);
			node (boost::shared_ptr <lambda_p_llvm::type::node> element_a);
			llvm::Type * type () override;
			llvm::PointerType * pointer_type ();
			boost::shared_ptr <lambda_p_llvm::type::node> element;
		};
	}
}


