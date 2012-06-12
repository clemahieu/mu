#include "extension3.h"

#include <mu/io/analyzer/expression.h>
#include <mu/core/expression.h>

void mu::io_test::extension3::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a)
{
	expression_a.self->dependencies.push_back (boost::shared_ptr <mu::core::node> ());
	expression_a.self->dependencies.push_back (boost::shared_ptr <mu::core::node> ());
}