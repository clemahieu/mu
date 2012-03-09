#pragma once

#include <mu/script/operation.h>

#include <vector>

namespace mu
{
    namespace script
    {
        namespace type_check
        {
			template <typename type1_t=void>
            class operation: public mu::script::operation
            {
			public:
                operation (boost::shared_ptr <mu::script::operation> target_a)
					: target (target_a)
				{
				}
                void perform (mu::script::context & context_a)
				{
					if (check_count (context_a.errors, context_a.parameters, 1))
					{
						if (boost::dynamic_pointer_cast <type1_t> (context_a.parameters [0]).get () != nullptr)
						{
							target->perform (context_a);
						}
						else
						{
							invalid_type (context_a.errors, context_a.parameters [0], 0);
						}
					}
				}
                boost::shared_ptr <mu::script::operation> target;
            };
			template <>
            class operation <void>: public mu::script::operation
            {
			public:
                operation (boost::shared_ptr <mu::script::operation> target_a)
					: target (target_a)
				{
				}
                void perform (mu::script::context & context_a)
				{
					if (check_count (context_a.errors, context_a.parameters, 0))
					{
						target->perform (context_a);
					}
				}
                boost::shared_ptr <mu::script::operation> target;
            };
        }
    }
}