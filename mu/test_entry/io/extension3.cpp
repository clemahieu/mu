#include <mu/test_entry/io/extension3.h>

#include <mu/io/analyzer/expression.h>
#include <mu/core/expression.h>

#include <assert.h>

void mu::io_test::extension3::operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a, mu::string remaining)
{
    assert (remaining.empty ());
	expression_a.self->dependencies.push_back (nullptr);
	expression_a.self->dependencies.push_back (nullptr);
}

bool mu::io_test::extension3::operator () ()
{
    return false;
}