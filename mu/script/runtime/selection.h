#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace runtime
		{
			class expression;
			class selection : public mu::script::operation
			{
			public:
				selection (boost::shared_ptr <mu::script::runtime::expression> expression_a, size_t index_a);
				bool operator () (mu::script::context & context_a) override;
				boost::shared_ptr <mu::script::runtime::expression> expression;
				size_t index;
			};
		}
	}
}