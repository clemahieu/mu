#pragma once

#include <mu/script/operation.h>
#include <mu/llvm_/execution_engine/node.h>
#include <mu/core/segment.h>

namespace llvm
{
	class Function;
}
namespace mu
{
    namespace core
    {
        class node;
        namespace errors
        {
            class error_target;
        }
    }
	namespace llvm_
	{
		namespace execution_engine
		{
			class node;
			class run_function : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
				void perform_internal (mu::script::context & context_a, boost::shared_ptr <mu::llvm_::execution_engine::node> one, llvm::Function * function);
				std::wstring name () override;
			};
		}
	}
}
