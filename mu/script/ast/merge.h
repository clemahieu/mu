#pragma once

#include <mu/script_runtime/operation.h>

namespace mu
{
	namespace script
	{
		namespace ast
		{
			class merge : public mu::script_runtime::operation
			{
			public:
				bool operator () (mu::script_runtime::context & context_a) override;
			};
		}
	}
}

