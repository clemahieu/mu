#include "binder_string_error.h"

lambda_p::errors::binder_string_error::binder_string_error (::std::wstring binder_name_a, ::std::wstring message_a)
	: message (message_a),
	binder_error (binder_name_a)
{
}

::lambda_p::errors::error_id lambda_p::errors::binder_string_error::error_type ()
{
	return ::lambda_p::errors::error_binder_string;
}

void lambda_p::errors::binder_string_error::string (::std::wostream & stream)
{
	stream << binder_name;
	stream << L' ';
	stream << message;
}
