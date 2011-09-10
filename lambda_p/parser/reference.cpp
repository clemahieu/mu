#include "reference.h"

lambda_p::parser::reference::reference(::std::wstring target_statement_a)
	: target_statement (target_statement_a)
{
}

lambda_p::parser::reference::~reference(void)
{
}

::lambda_p::parser::state_id lambda_p::parser::reference::state_type ()
{
	return lambda_p::parser::state_result_ref;
}
