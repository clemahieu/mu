#pragma once

#include <mu/core/node.h>

#include <boost/filesystem.hpp>

namespace mu
{
    namespace script
    {
        namespace file
        {
            class path : public mu::core::node
            {
            public:
                path (boost::filesystem::path const & path_a);
                boost::filesystem::path path_m;
            };
        }
    }
}