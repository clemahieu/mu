#include <lambda_p/parser/reference_identifiers.h>

lambda_p::parser::reference_identifiers::reference_identifiers(::std::wstring & statement_a, ::std::wstring & argument_a)
	: statement (statement_a),
	argument (argument_a)
{
}

lambda_p::parser::reference_identifiers::~reference_identifiers(void)
{
}

bool lambda_p::parser::reference_identifiers::operator < (::lambda_p::parser::reference_identifiers const & other) const
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