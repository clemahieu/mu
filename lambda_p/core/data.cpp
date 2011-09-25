#include <lambda_p/core/data.h>

#include <lambda_p/core/routine.h>

lambda_p::core::data::data(::std::wstring string_a)
	: string_m (string_a)
{
}

lambda_p::core::data::~data(void)
{
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