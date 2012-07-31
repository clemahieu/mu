#include <mu/script/parser/parser.h>

#include <mu/script/parser/state.h>

void mu::script::parser::parser::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    mu::script::parser::state & item (*state.top ());
    item (token_a, context_a);
}