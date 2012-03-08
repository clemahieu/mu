#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace llvm_
	{
		namespace instructions
		{
			class call : public mu::script::operation
			{
			public:
				void perform (mu::script::context & context_a) override;
			};
		}
	}
}
