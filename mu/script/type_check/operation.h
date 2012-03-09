#pragma once

#include <mu/script/operation.h>
#include <mu/script/check.h>

#include <vector>

namespace mu
{
    namespace script
    {
        namespace type_check
        {
			template <typename type1_t=void, typename type2_t=void, typename type3_t=void, typename type4_t=void, typename type5_t=void>
            class operation: public mu::script::operation
            {
			public:
                operation (boost::shared_ptr <mu::script::operation> target_a)
					: target (target_a)
				{
				}
                void perform (mu::script::context & context_a)
				{
					if (mu::script::check <type1_t, type2_t, type3_t, type4_t, type5_t> () (context_a))
					{
						target->perform (context_a);
					}
				}
                boost::shared_ptr <mu::script::operation> target;
            };
        }
    }
}