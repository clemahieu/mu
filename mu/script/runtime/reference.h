#pragma once

#include <mu/script/runtime/node.h>

namespace mu
{
	namespace script
	{
		namespace runtime
		{
			class reference : public mu::script::runtime::node
			{
			public:
				reference (size_t expression_a, size_t index_a);
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::runtime::frame & frame, std::vector <boost::shared_ptr <mu::core::node>> & target) override;
				size_t expression;
				size_t index;
			};
		}
	}
}
