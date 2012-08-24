#include <mu/test_entry/io/extension4.h>

#include <mu/io/keywording/keywording.h>
#include <mu/io/tokens/value.h>
#include <mu/core/node.h>

#include <assert.h>

#include <gc_cpp.h>

mu::io_test::extension4::extension4 (mu::io::keywording::keywording & keywording_a)
    : first (true),
    keywording (keywording_a)
{
}

void mu::io_test::extension4::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    if (first)
    {
        first = false;
    }
    else
    {
        keywording.target (new (GC) mu::io::tokens::value (new (GC) mu::core::node), mu::io::debugging::context ());
    }
}