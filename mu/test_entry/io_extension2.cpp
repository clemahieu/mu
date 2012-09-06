#include <mu/test_entry/io_extension2.h>

#include <mu/io/analyzer_analyzer.h>
#include <mu/io/tokens_value.h>
#include <mu/core/node.h>

#include <gc_cpp.h>

#include <assert.h>

mu::io_test::extension2::extension2 (mu::io::analyzer::analyzer & analyzer_a):
analyzer (analyzer_a)
{
}

void mu::io_test::extension2::operator () (mu::io::tokens::token const & token_a)
{
    analyzer.target (mu::io::tokens::value (token_a.context, new (GC) mu::core::node));
}