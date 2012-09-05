#include <mu/test_entry/io_extension2.h>

#include <mu/io/analyzer_analyzer.h>
#include <mu/io/tokens_value.h>
#include <mu/core/node.h>

#include <gc_cpp.h>

#include <assert.h>

mu::io_test::extension2::extension2 (mu::io::keywording::keywording & keywording_a):
keywording (keywording_a)
{
}

void mu::io_test::extension2::operator () (mu::io::tokens::token * token_a)
{
    keywording.target (new (GC) mu::io::tokens::value (token_a->context, new (GC) mu::core::node));
}