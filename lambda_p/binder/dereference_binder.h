#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p
{
    namespace binder
    {        
        class dereference_binder : public ::lambda_p::binder::node_binder
        {
        public:
            dereference_binder (void);
            ~dereference_binder (void);
            virtual void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems);
            virtual void operator () ();
        private:
            void bind_good (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems);
        };
    }
}

