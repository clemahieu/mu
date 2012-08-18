#include <mu/script/parser/parser.h>

#include <mu/script/parser/state.h>
#include <mu/script/parser/cluster.h>

#include <gc_cpp.h>

mu::script::parser::parser::parser (mu::core::errors::error_target & errors_a, boost::function <void (mu::script::ast::cluster *)> target_a):
errors (errors_a),
target (target_a)
{
    state.push (new (GC) mu::script::parser::cluster (*this));
}

void mu::script::parser::parser::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    mu::script::parser::state & item (*state.top ());
    item (token_a, context_a);
}