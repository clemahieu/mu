#include "unexpected_result_count.h"

lambda_p::errors::unexpected_result_count::unexpected_result_count (::std::wstring binder_name_a, size_t actual_a, size_t expected_a)
	: actual (actual_a),
	expected (expected_a),
	binder_error (binder_name_a)
{
}

::lambda_p::errors::error_id lambda_p::errors::unexpected_result_count::error_type ()
{
	return ::lambda_p::errors::error_unexpected_result_count;
}

void lambda_p::errors::unexpected_result_count::string (::std::wostream & stream)
{
	stream << binder_name;
	stream << L" is expecting ";
	stream << expected;
	stream << L" results, have; ";
	stream << actual;
	stream << L'\n';
}
