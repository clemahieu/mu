#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace ast
		{
			class read_from_file : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
			};
		}
	}
}
