#pragma once

#include <mu/script/fixed.h>

#include <llvm/ExecutionEngine/GenericValue.h>

namespace mu
{
	namespace llvm_
	{
		namespace execution_engine
		{
			namespace generic_value
			{
				class create_int : public mu::script::fixed
				{
				public:
					void operator () (mu::script::context & context_a) override;
					size_t count () override;
				};
			}
		}
	}
}
