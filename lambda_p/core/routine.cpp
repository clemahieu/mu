#include <lambda_p/core/routine.h>

lambda_p::core::routine::routine(size_t parameters_a)
	: parameters (parameters_a)
{
}

lambda_p::core::routine::~routine(void)
{
}

::lambda_p::core::statement * lambda_p::core::routine::add_statement ()
{
	statements.push_back (::lambda_p::core::statement (this, statements.size ()));
	return &statements [statements.size () - 1];
}

::lambda_p::core::data * lambda_p::core::routine::add_data (::boost::shared_array <uint8_t> item_a, size_t size_a, size_t statement_a, size_t index_a)
{
	data.push_back (::lambda_p::core::data (item_a, size_a, this, statement_a, index_a));
	return &data[data.size () - 1];
}

::lambda_p::core::parameter_ref * lambda_p::core::routine::add_parameter_ref (size_t index_a)
{
	parameter_refs.push_back (::lambda_p::core::parameter_ref (this, index_a));
	return &parameter_refs [parameter_refs.size () - 1];
}

::lambda_p::core::result * lambda_p::core::routine::add_result (size_t statement_a, size_t index_a)
{
	results.push_back (::lambda_p::core::result (this, statement_a, index_a));
	return &results [results.size () - 1];
}

::lambda_p::core::result_ref * lambda_p::core::routine::add_result_ref (size_t statement_a, size_t index_a)
{
	result_refs.push_back (::lambda_p::core::result_ref (this, statement_a, index_a));
	return &result_refs [result_refs.size () - 1];
}