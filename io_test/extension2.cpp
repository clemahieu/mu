#include "extension2.h"

#include <io/analyzer/expression.h>
#include <core/expression.h>

void mu::io_test::extension2::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a)
{
	expression_a.self->dependencies.push_back (boost::shared_ptr <mu::core::node> ());
}