#pragma once

#include <mu/script/node.h>

namespace mu
{
	namespace script
	{
		class constant : public mu::script::node
		{
		public:
			constant (boost::shared_ptr <mu::core::node> value_a);
			void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target) override;
			boost::shared_ptr <mu::core::node> value;
		};
	}
}

