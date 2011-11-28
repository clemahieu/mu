#include "number_binder_test.h"

#include <lambda_p_kernel/number_binder.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_kernel/nodes/number.h>

void lambda_p_test::number_binder_test::run ()
{
	run_1 ();
}

void lambda_p_test::number_binder_test::run_1 ()
{
	lambda_p_kernel::number_binder number_binder;
	boost::shared_ptr <lambda_p_kernel::nodes::number> number;
	lambda_p::errors::error_list problems;
	number_binder.core (std::wstring (L"d4"), number, problems);
	assert (number->value == 4);
}