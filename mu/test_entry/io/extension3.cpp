#include <mu/test_entry/io/extension3.h>

#include <mu/io/keywording_keywording.h>
#include <mu/io/tokens_value.h>
#include <mu/core/node.h>

#include <assert.h>

#include <gc_cpp.h>

mu::io_test::extension3::extension3 (mu::io::keywording::keywording & keywording_a)
    : keywording (keywording_a)
{
}

void mu::io_test::extension3::operator () (mu::io::tokens::token * token_a)
{
    keywording.target (new (GC) mu::io::tokens::value (token_a->context, new (GC) mu::core::node));
    keywording.target (new (GC) mu::io::tokens::value (token_a->context, new (GC) mu::core::node));
}