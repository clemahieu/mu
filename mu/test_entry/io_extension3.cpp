#include <mu/test_entry/io_extension3.h>

#include <mu/io/analyzer_analyzer.h>
#include <mu/io/tokens_value.h>
#include <mu/core/node.h>

#include <assert.h>

#include <gc_cpp.h>

mu::io_test::extension3::extension3 (mu::io::analyzer::analyzer & analyzer_a):
analyzer (analyzer_a)
{
}

void mu::io_test::extension3::operator () (mu::io::tokens::token const & token_a)
{
    analyzer.target (mu::io::tokens::value (token_a.context, new (GC) mu::core::node));
    analyzer.target (mu::io::tokens::value (token_a.context, new (GC) mu::core::node));
}