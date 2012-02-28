#pragma once

#include <mu/script/runtime/node.h>

namespace mu
{
	namespace core
	{
		class routine;
	}
	namespace script
	{
		namespace runtime
		{
			class remap : public mu::script::runtime::node
			{
			public:
				remap (boost::shared_ptr <mu::core::routine> routine_a);
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::runtime::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target) override;
				boost::shared_ptr <mu::core::routine> routine;
			};
		}
	}
}

