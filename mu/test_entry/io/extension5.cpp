#include <mu/test_entry/io/extension5.h>

#include <mu/io/analyzer/expression.h>
#include <mu/core/expression.h>

void mu::io_test::extension5::operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a, mu::string remaining)
{
}

bool mu::io_test::extension5::operator () ()
{
    return true;
}