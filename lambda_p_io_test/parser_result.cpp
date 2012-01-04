#include "parser_result.h"

void lambda_p_io_test::parser_result::operator () (boost::shared_ptr <lambda_p_io::ast::expression> result_a)
{
	results.push_back (result_a);
}