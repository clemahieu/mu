#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p
{
	namespace binder
	{
		class data_to_string_binder : public ::lambda_p::binder::node_binder
		{
		public:
			data_to_string_binder (void);
			~data_to_string_binder (void);
			void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);			
			void operator () ();
		};
	}
}

