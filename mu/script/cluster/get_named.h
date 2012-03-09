#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace cluster
		{
			class get_named : public mu::script::operation
			{
			public:
				void operator () (mu::script::context & context_a) override;
			};
		}
	}
}

