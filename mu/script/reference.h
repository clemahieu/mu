#pragma once

#include <mu/script/node.h>

namespace mu
{
	namespace script
	{
		class reference : public mu::script::node
		{
		public:
			reference (size_t expression_a, size_t index_a);
			void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target) override;
			size_t expression;
			size_t index;
		};
	}
}
