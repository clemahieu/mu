#pragma once

#include <mu/script/operation.h>
#include <mu/llvm_/operation.h>

namespace mu
{
    namespace core
    {
        namespace errors
        {
            class error_target;
        }
    }
	namespace llvm_
	{
        namespace value
        {
            class node;
        }
		namespace instructions
		{
			class add : public mu::script::operation, public mu::llvm_::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
                bool operator () (mu::llvm_::ctx & context_a) override;
                auto core (mu::core::errors::error_target & errors_a, mu::llvm_::value::node * one, mu::llvm_::value::node * two) -> mu::llvm_::value::node *;
			};
		}
	}
}
