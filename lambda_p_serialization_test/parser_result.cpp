#include "parser_result.h"

void lambda_p_serialization_test::parser_result::operator () (boost::shared_ptr <lambda_p_serialization::ast::expression> result_a)
{
	results.push_back (result_a);
}