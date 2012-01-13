#include "extension4.h"

#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p/call.h>

void lambda_p_io_test::extension4::operator () (lambda_p_io::analyzer::expression & expression_a)
{
	++expression_a.position;
	expression_a.self->dependencies.push_back (boost::shared_ptr <lambda_p::node> ());
}