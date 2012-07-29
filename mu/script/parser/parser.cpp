#include <mu/script/parser/parser.h>

void mu::script::parser::parser::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    auto item (stack.top ());
    item (token_a, context_a);
}