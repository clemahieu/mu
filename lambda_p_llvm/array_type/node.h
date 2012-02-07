#pragma once

#include <lambda_p_llvm/type/node.h>

#include <boost/shared_ptr.hpp>

namespace llvm
{
	class ArrayType;
}
namespace lambda_p_llvm
{
	namespace array_type
	{
		class node : public lambda_p_llvm::type::node
		{
		public:
			node (boost::shared_ptr <lambda_p_llvm::type::node> element_a, size_t count_a);
			llvm::Type * type () override;
			llvm::ArrayType * array_type ();
			boost::shared_ptr <lambda_p_llvm::type::node> element;
			size_t count;
		};
	}
}

