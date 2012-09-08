#pragma once

#include <mu/core/node.h>

#include <boost/filesystem/fstream.hpp>
#include <boost/noncopyable.hpp>

namespace mu
{
    namespace script
    {
        namespace file
        {
            class node : public mu::core::node, boost::noncopyable
            {
            public:
                node (boost::filesystem3::path const & path);
                ~node ();
                boost::filesystem3::fstream stream;
            };
        }
    }
}