#include <mu/test_entry/io/extension3.h>

#include <mu/io/analyzer/expression.h>
#include <mu/core/expression.h>

#include <assert.h>

mu::io_test::extension3::extension3 (mu::io::keywording::keywording & keywording_a)
: keywording (keywording_a)
{
}

void mu::io_test::extension3::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    
}