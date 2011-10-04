#include "unexpected_argument_count.h"

lambda_p::errors::unexpected_argument_count::unexpected_argument_count (::std::wstring binder_name_a, size_t actual_a, size_t expected_a)
	: binder_error (binder_name_a),
	actual (actual_a),
	expected (expected_a)
{
}

::lambda_p::errors::error_id lambda_p::errors::unexpected_argument_count::error_type ()
{
	return ::lambda_p::errors::error_unexpected_argument_count;
}

void lambda_p::errors::unexpected_argument_count::string (::std::wostream & stream)
{
	stream << binder_name;
	stream << L" is expecting ";
	stream << expected;
	stream << L" arguments, have: ";
	stream << actual;
	stream << L'\n';
}

