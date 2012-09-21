#pragma once

#include <mu/script/operation.h>

namespace boost
{
    namespace filesystem
    {
        class path;
    }
}
namespace mu
{
    namespace script
    {
        namespace file
        {
            class node;
            class path;
            class open : public mu::script::operation
            {
            public:
                bool operator () (mu::script::context & context_a) override;
                static auto core (boost::filesystem::path const & path) -> mu::script::file::node *;
            };
        }
    }
}