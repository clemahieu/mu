#pragma once

#include <core/node.h>

namespace llvm
{
	class Module;
}
namespace lambda_p_llvm
{
	namespace module
	{
		class node : public mu::core::node
		{
		public:
			node (llvm::Module * module_a);
			std::wstring debug () override;
			llvm::Module * module;
		};
	}
}

