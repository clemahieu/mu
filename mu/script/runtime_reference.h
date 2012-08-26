#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace runtime
		{
			class expression;
			class reference : public mu::script::operation
			{
			public:
				reference (mu::script::runtime::expression * expression_a);
				bool operator () (mu::script::context & context_a) override;
				mu::script::runtime::expression * expression;
			};
		}
	}
}