#pragma once

#include <lambda_p/errors/binder_error.h>
#include <lambda_p/core/node.h>

namespace lambda_p
{
	namespace errors
	{
		class unexpected_node_type : public ::lambda_p::errors::binder_error
		{
		public:
			unexpected_node_type (::std::wstring binder_name_a, size_t position_a, ::lambda_p::core::node_id id_a);
            error_id error_type ();
            void string (::std::wostream & stream);
			::lambda_p::core::node_id id;
			size_t position;
		};	
	}
}
