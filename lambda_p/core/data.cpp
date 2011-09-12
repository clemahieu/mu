#include <lambda_p/core/data.h>

#include <lambda_p/core/routine.h>

lambda_p::core::data::data(::std::wstring string_a, ::lambda_p::core::routine * routine_a, size_t self_statement_a, size_t self_argument_a)
	: routine (routine_a),
	string_m (string_a),
	self_statement (self_statement_a),
	self_argument (self_argument_a)
{
}

lambda_p::core::data::~data(void)
{
}

void lambda_p::core::data::validate (::std::wostream & problems) const
{
	validate_argument (L"data: ", routine, self_statement, self_argument, problems);
}

::std::wstring lambda_p::core::data::string () const
{
    return string_m;
}

::lambda_p::core::node_id lambda_p::core::data::node_type () const
{
	return ::lambda_p::core::node_data;
}

::std::wstring lambda_p::core::data::node_type_name () const
{
	return ::std::wstring (L"data");
}