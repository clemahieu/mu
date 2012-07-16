#pragma once

#include <mu/core/errors/error_target.h>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class null : public mu::core::errors::error_target
			{
			public:
				null ();
				void operator () (mu::core::errors::error * error) override;
				bool operator () () override;
                void print (mu::ostream & target) override;
				void operator () (mu::string error) override;
				void operator () (char32_t const * error) override;
				bool had_error;
			};
		}
	}
}