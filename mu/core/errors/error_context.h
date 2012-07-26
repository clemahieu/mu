#pragma once

#include <mu/core/errors/error_target.h>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error_context : public mu::core::errors::error_target
			{
			public:
				error_context (mu::core::errors::error_target & target_a, mu::io::debugging::context context_a);
				void operator () (mu::core::errors::error * error) override;
				bool operator () () override;
                void print (mu::ostream & target) override;
				mu::core::errors::error_target & target;
				mu::io::debugging::context context;
			};
		}
	}
}
