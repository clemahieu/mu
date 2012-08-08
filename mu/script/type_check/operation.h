#pragma once

#include <mu/script/operation.h>
#include <mu/core/check.h>

#include <vector>

namespace mu
{
    namespace script
    {
        namespace type_check
        {
			template <typename ...T>
            class operation: public mu::script::operation
            {
			public:
                operation (mu::script::operation * target_a)
					: target (target_a)
				{
				}
                bool operator () (mu::script::context & context_a)
				{
					bool result (true);
					if (mu::core::check <T...> (context_a))
					{
						(*target) (context_a);
					}
					else
					{
						result = false;
					}
					return result;
				}
                mu::script::operation * target;
            };
        }
    }
}