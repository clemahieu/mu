#pragma once

#include <mu/script/operation.h>
#include <mu/llvm_/execution_engine.node.h>

namespace llvm
{
	class Function;
}
namespace mu
{
	namespace llvm_
	{
		namespace execution_engine
		{
			class node;
			class run_function : public mu::script::operation
			{
			public:
				void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				void perform_internal (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::llvm_::execution_engine::node> one, llvm::Function * function, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results);
				std::wstring name () override;
			};
		}
	}
}
