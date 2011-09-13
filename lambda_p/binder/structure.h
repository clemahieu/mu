#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p
{
	namespace core
	{
		class data;
	}
    namespace binder
    {        
        class structure : public ::lambda_p::binder::node_binder
        {
        public:
            structure (void);
            ~structure (void);
            virtual void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems);
            virtual void operator () ();			
            ::std::map < ::std::wstring, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > nodes;
        private:
            void bind_good (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems);
			void fetch_child (::boost::shared_ptr < ::lambda_p::binder::structure> & intermediate, ::boost::shared_ptr < ::lambda_p::binder::node_instance> & node, size_t argument_number, ::lambda_p::core::data * data, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);
        };
    }
}

