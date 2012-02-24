#pragma once

#include <mu/script/node.h>

namespace mu
{
	namespace script
	{
		class parameters : public mu::script::node
		{
		public:
			void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target) override;
		};
	}
}
