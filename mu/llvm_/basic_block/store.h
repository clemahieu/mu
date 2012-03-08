#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace llvm_
	{
		namespace basic_block
		{
			class store : public mu::script::fixed
			{
			public:
				void operator () (mu::script::context & context_a) override;
				size_t count () override;
			};
		}
	}
}
