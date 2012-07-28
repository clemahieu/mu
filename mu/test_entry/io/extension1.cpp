#include <mu/test_entry/io/extension1.h>

mu::io_test::extension1::extension1 (mu::io::keywording::keywording & keywording_a)
    : keywording (keywording_a)
{
}

void mu::io_test::extension1::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
}