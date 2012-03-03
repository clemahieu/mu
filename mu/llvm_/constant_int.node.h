#pragma once

#include <mu/llvm_/constant.node.h>

namespace llvm
{
	class ConstantInt;
}
namespace mu
{
	namespace llvm_
	{
		namespace constant_int
		{
			class node : public mu::llvm_::constant::node
			{
			public:
				node (llvm::ConstantInt * constant_int_a, boost::shared_ptr <mu::llvm_::type::node> type_a);
				std::wstring name () override;
				llvm::ConstantInt * constant_int ();
			};
		}
	}
}
