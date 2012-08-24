#include <mu/test_entry/io/extension3.h>

#include <mu/core/expression.h>
#include <mu/io/keywording/keywording.h>
#include <mu/io/tokens/value.h>

#include <assert.h>

#include <gc_cpp.h>

mu::io_test::extension3::extension3 (mu::io::keywording::keywording & keywording_a)
    : keywording (keywording_a)
{
}

void mu::io_test::extension3::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    keywording.target (new (GC) mu::io::tokens::value (new (GC) mu::core::node), mu::io::debugging::context ());
    keywording.target (new (GC) mu::io::tokens::value (new (GC) mu::core::node), mu::io::debugging::context ());
}