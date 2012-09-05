#include <mu/test_entry/io_extension5.h>

#include <mu/core/node.h>
#include <mu/io/keywording_keywording.h>

mu::io_test::extension5::extension5 (mu::io::keywording::keywording & keywording_a):
keywording (keywording_a)
{
}

void mu::io_test::extension5::operator () (mu::io::tokens::token * token_a)
{
    keywording.state.pop ();
    keywording (token_a);
}