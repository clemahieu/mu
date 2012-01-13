#include "global.h"

#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p/expression.h>

lambda_p_io::analyzer::global::global (boost::shared_ptr <lambda_p::node> node_a)
	: node (node_a)
{
}

void lambda_p_io::analyzer::global::operator () (lambda_p_io::analyzer::expression & expression_a)
{
	expression_a.self->dependencies.push_back (node);
}