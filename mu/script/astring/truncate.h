#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace astring
		{
			class truncate : public mu::script::operation
			{
			public:
				void operator () (mu::script::context & context_a) override;
			};
		}
	}
}
