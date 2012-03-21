#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace llvm_
	{
		namespace instructions
		{
			class cmpxchg : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
			};
		}
	}
}
