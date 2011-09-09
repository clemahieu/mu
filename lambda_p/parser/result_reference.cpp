#include <lambda_p/parser/result_reference.h>

lambda_p::parser::result_reference::result_reference(::std::wstring & statement_a, ::std::wstring & argument_a)
	: statement (statement_a),
	argument (argument_a)
{
}

lambda_p::parser::result_reference::~result_reference(void)
{
}

bool lambda_p::parser::result_reference::operator < (::lambda_p::parser::result_reference const & other) const
{
	int comparison (statement.compare (other.statement));
	bool result;
	if (comparison == 0)
	{
		result = argument < other.argument;
	}
	else
	{
		result = comparison < 0;
	}
	return result;
}