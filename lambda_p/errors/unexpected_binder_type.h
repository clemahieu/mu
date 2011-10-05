#pragma once

#include <lambda_p/errors/binder_error.h>
#include <lambda_p/core/node.h>

namespace lambda_p
{
	namespace errors
	{
		class unexpected_binder_type : public ::lambda_p::errors::binder_error
		{
		public:
			unexpected_binder_type (::std::wstring binder_name_a, size_t position_a, ::std::wstring expected_type_a);
            error_id error_type ();
            void string (::std::wostream & stream);
			::std::wstring expected_type;
			size_t position;
		};	
	}
}
