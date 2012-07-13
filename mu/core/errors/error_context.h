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
				error_context (boost::shared_ptr <mu::core::errors::error_target> target_a, mu::io::debugging::context context_a);
				void operator () (mu::core::errors::error * error) override;
				bool operator () () override;
                void print (std::wostream & target) override;
				boost::shared_ptr <mu::core::errors::error_target> target;
				mu::io::debugging::context context;
			};
		}
	}
}
