#include "extension3.h"

#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p/call.h>

void lambda_p_io_test::extension3::operator () (lambda_p_io::analyzer::expression & expression_a)
{
	expression_a.result->dependencies.push_back (boost::shared_ptr <lambda_p::node> ());
	expression_a.result->dependencies.push_back (boost::shared_ptr <lambda_p::node> ());
}