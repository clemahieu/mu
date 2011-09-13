#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/core/node.h>
#include <lambda_p/binder/node_instance.h>

#include <map>

namespace lambda_p
{
    namespace binder
    {
        class dereference : public ::lambda_p::binder::node_instance
        {
        public:
            dereference (void);
            ~dereference (void);
            void operator () ();
            ::std::map < ::std::wstring, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > nodes;
        };
    }
}

