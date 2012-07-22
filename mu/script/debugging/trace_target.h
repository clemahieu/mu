#pragma once

#include <mu/core/errors/error_target.h>

namespace mu
{
	namespace script
	{
		class context;
		namespace debugging
		{
			class trace_target : public mu::core::errors::error_target
			{
			public:
				trace_target (mu::core::errors::error_target * target_a, mu::script::context & context_a);
				void operator () (mu::core::errors::error * error) override;
				bool operator () () override;
                void print (mu::ostream & target) override;
				mu::core::errors::error_target * target;
				mu::script::context & context;
			};
		}
	}
}