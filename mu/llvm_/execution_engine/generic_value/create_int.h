#pragma once

#include <mu/script/operation.h>

#include <llvm/ExecutionEngine/GenericValue.h>

namespace mu
{
	namespace llvm_
	{
		namespace execution_engine
		{
			namespace generic_value
			{
				class create_int : public mu::script::operation
				{
				public:
					bool operator () (mu::script::context & context_a) override;
				};
			}
		}
	}
}
