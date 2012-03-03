#pragma once

#include <mu/llvm_/type.node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace llvm
{
	class FunctionType;
}
namespace mu
{
	namespace llvm_
	{
		namespace context
		{
			class node;
		}
		namespace function_type
		{
			class node : public mu::llvm_::type::node
			{
			public:
                node (boost::shared_ptr <mu::llvm_::context::node> context_a, llvm::FunctionType * function_type_a);
				node (boost::shared_ptr <mu::llvm_::context::node> context_a, std::vector <boost::shared_ptr <mu::llvm_::type::node>> parameters_a, boost::shared_ptr <mu::llvm_::type::node> output_a);
                llvm::Type * type () override;
                llvm::FunctionType * function_type ();
				boost::shared_ptr <mu::llvm_::context::node> context;
				std::vector <boost::shared_ptr <mu::llvm_::type::node>> parameters;
				boost::shared_ptr <mu::llvm_::type::node> output;
			};
		}
	}
}
