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
                operation (boost::shared_ptr <mu::script::operation> target_a);
                void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
                std::vector <std::type_info const &> type_ids;
                boost::shared_ptr <mu::script::operation> target;
            };
        }
    }
}