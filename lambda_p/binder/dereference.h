#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p
{
    namespace binder
    {        
        class dereference : public ::lambda_p::binder::node_binder
        {
        public:
            dereference (void);
            ~dereference (void);
            virtual void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems);
            virtual void operator () ();			
            ::std::map < ::std::wstring, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > nodes;
        private:
            void bind_good (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems);
        };
    }
}

