#include "node_out_of_order.h"

lambda_p::errors::node_out_of_order::node_out_of_order(size_t statement_number_a, size_t result_number_a)
	: statement_number (statement_number_a),
	result_number (result_number_a)
{
}

lambda_p::errors::error_id lambda_p::errors::node_out_of_order::error_type ()
{
	return lambda_p::errors::error_node_out_of_order;
}

void lambda_p::errors::node_out_of_order::string (std::wostream & stream)
{
	stream << L"Out of order node in statement: ";
	stream << statement_number;
	stream << L" result number: ";
	stream << result_number;
}