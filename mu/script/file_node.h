#pragma once

#include <mu/core/node.h>

#include <boost/filesystem/fstream.hpp>

namespace mu
{
    namespace script
    {
        namespace file
        {
            class node : public mu::core::node
            {
            public:
                node (boost::filesystem3::path const & path);
                boost::filesystem3::fstream stream;
            };
        }
    }
}