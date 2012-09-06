#include <mu/test_entry/io_extension5.h>

#include <mu/core/node.h>
#include <mu/io/analyzer_analyzer.h>

mu::io_test::extension5::extension5 (mu::io::analyzer::analyzer & analyzer_a):
analyzer (analyzer_a)
{
}

void mu::io_test::extension5::operator () (mu::io::tokens::token const & token_a)
{
    analyzer.state.pop ();
    analyzer (token_a);
}