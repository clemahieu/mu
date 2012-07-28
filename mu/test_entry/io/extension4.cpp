#include <mu/test_entry/io/extension4.h>

#include <mu/io/analyzer/expression.h>
#include <mu/core/expression.h>

#include <assert.h>

mu::io_test::extension4::extension4 (mu::io::keywording::keywording & keywording_a)
: keywording (keywording_a)
{
}

void mu::io_test::extension4::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    
}