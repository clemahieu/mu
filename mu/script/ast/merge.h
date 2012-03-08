#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace ast
		{
			class merge : public mu::script::operation
			{
			public:
				void perform (mu::script::context & context_a) override;
			};
		}
	}
}

