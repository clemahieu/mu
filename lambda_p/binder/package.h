#pragma once

#include <lambda_p/binder/node_binder.h>

#include <boost/enable_shared_from_this.hpp>

namespace lambda_p
{
    namespace binder
    {        
		class data;
        class package : public ::lambda_p::binder::node_binder, public ::boost::enable_shared_from_this < ::lambda_p::binder::package>
        {
        public:
            package (void);
            ~package (void);
            virtual void bind (::lambda_p::core::statement * statement, ::std::map < size_t, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
			::std::map < ::std::wstring, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > nodes;
			::std::wstring binder_name ();
		private:
			void parse_one (::std::map < size_t, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::boost::shared_ptr < ::lambda_p::binder::data> node, size_t result, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
        };
    }
}

