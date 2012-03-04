#pragma once

#include <mu/script/runtime/node.h>

namespace mu
{
	namespace script
	{
		namespace runtime
		{
			// Internal node to link all values of an expression, e.g. the expression [c] that references the `c' in some other [a; b; c]
			class expression : public mu::script::runtime::node
			{
			public:
				expression (size_t index_a);
				size_t index;
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::runtime::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target) override;
			};
		}
	}
}
