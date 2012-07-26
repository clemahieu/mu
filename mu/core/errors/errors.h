#pragma once

#include <mu/core/errors/error_target.h>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class errors : public mu::core::errors::error_target
			{
			public:
				errors (mu::core::errors::error_target & target_a);
				void operator () (mu::core::errors::error * error) override;
				bool operator () () override;
                void print (mu::ostream & target) override;
				void operator () (mu::string error) override;
				void operator () (char32_t const * error) override;
				mu::core::errors::error_target & target;
			};
		}
	}
}