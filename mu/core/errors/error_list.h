#pragma once

#include <mu/core/errors/error_target.h>

#include <vector>

#include <gc_allocator.h>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error;
			class error_list : public mu::core::errors::error_target
			{
			public:
				std::vector <mu::core::errors::error *, gc_allocator <mu::core::errors::error>> errors;
				void operator () (mu::core::errors::error * error) override;
				bool operator () () override;
                void print (mu::ostream & target) override;
			};
		}
	}
}
