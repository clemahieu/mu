#pragma once

#include <mu/script/operation.h>

namespace mu
{
    namespace script
    {
        namespace file
        {
            class path;
            class path_from_string : public mu::script::operation
            {
            public:
                bool operator () (mu::script::context & context_a) override;
                static auto core (mu::string const & string_a) -> mu::script::file::path *;
            };
        }
    }
}