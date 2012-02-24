#include "extension4.h"

#include <lambda_p_io/analyzer/expression.h>
#include <core/expression.h>

void lambda_p_io_test::extension4::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a)
{
	++expression_a.position;
	expression_a.self->dependencies.push_back (boost::shared_ptr <mu::core::node> ());
}