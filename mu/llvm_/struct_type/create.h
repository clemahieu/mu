#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace llvm_
	{
		namespace struct_type
		{
			class create : public mu::script::operation
			{
			public:
				void perform (mu::script::context & context_a) override;
			};
		}
	}
}
