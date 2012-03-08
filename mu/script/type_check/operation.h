#pragma once

#include <mu/script/operation.h>

#include <vector>
#include <typeinfo>

namespace mu
{
    namespace script
    {
        namespace type_check
        {
            class operation : public mu::script::operation
            {
			public:
                operation (boost::shared_ptr <mu::script::operation> target_a);
                void perform (mu::script::context & context_a) override;
                std::vector <std::type_info const *> type_ids;
                boost::shared_ptr <mu::script::operation> target;
            };
        }
    }
}