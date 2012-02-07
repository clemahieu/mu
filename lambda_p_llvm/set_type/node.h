#pragma once

#include <lambda_p_llvm/struct_type/node.h>

namespace lambda_p_llvm
{
	namespace set_type
	{
		class node : public lambda_p_llvm::struct_type::node
		{
		public:			
			node (boost::shared_ptr <lambda_p_llvm::context::node> context_a, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> elements_a);
			node (boost::shared_ptr <lambda_p_llvm::struct_type::node> struct_a);
		};
	}
}

