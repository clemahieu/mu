#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace values
		{
			class create : public mu::script::operation
			{
			public:
				void operator () (mu::script::context & context_a) override;
			};
		}
	}
}
