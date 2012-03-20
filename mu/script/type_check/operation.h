#pragma once

#include <mu/script_runtime/operation.h>
#include <mu/script/check.h>

#include <vector>

namespace mu
{
    namespace script
    {
        namespace type_check
        {
			template <typename type1_t=void, typename type2_t=void, typename type3_t=void, typename type4_t=void, typename type5_t=void>
            class operation: public mu::script_runtime::operation
            {
			public:
                operation (boost::shared_ptr <mu::script_runtime::operation> target_a)
					: target (target_a)
				{
				}
                bool operator () (mu::script_runtime::context & context_a)
				{
					bool result (true);
					if (mu::script::check <type1_t, type2_t, type3_t, type4_t, type5_t> () (context_a))
					{
						(*target) (context_a);
					}
					else
					{
						result = false;
					}
					return result;
				}
                boost::shared_ptr <mu::script_runtime::operation> target;
            };
        }
    }
}