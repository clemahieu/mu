#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace llvm_
	{
		namespace set_type
		{
			class extract : public mu::script::fixed
			{
			public:
				void operator () (mu::script::context & context_a) override;
				size_t count () override;
			};
		}
	}
}
