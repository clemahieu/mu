#pragma once

#include <mu/script/runtime/node.h>

namespace mu
{
	namespace script
	{
		namespace runtime
		{
			class constant : public mu::script::runtime::node
			{
			public:
				constant (boost::shared_ptr <mu::core::node> value_a);
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::runtime::frame & frame, std::vector <boost::shared_ptr <mu::core::node>> & target) override;
				boost::shared_ptr <mu::core::node> value;
			};
		}
	}
}

