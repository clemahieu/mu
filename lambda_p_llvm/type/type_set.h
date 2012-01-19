#pragma once

#include <lambda_p_llvm/type/node.h>

namespace llvm
{
	class StructType;
}
namespace lambda_p_llvm
{
	namespace type
	{
		class type_set : public lambda_p_llvm::type::node
		{
		public:			
			type_set (llvm::StructType * type_a);
			llvm::StructType * struct_type ();
		};
	}
}

