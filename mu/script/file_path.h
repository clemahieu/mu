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
                path (boost::filesystem3::path const & path_a);
                boost::filesystem3::path path_m;
            };
        }
    }
}