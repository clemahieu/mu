#include <mu/test_entry/io/extension2.h>

#include <mu/io/keywording/keywording.h>
#include <mu/io/tokens/value.h>
#include <mu/core/node.h>

#include <gc_cpp.h>

#include <assert.h>

mu::io_test::extension2::extension2 (mu::io::keywording::keywording & keywording_a)
: keywording (keywording_a)
{
}

void mu::io_test::extension2::operator () (mu::io::tokens::token * token_a, mu::io::context context_a)
{
    keywording.target (new (GC) mu::io::tokens::value (new (GC) mu::core::node), context_a);
}