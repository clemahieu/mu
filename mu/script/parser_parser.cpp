#include <mu/script/parser_parser.h>

#include <mu/script/parser_state.h>
#include <mu/script/parser_cluster.h>

#include <gc_cpp.h>

mu::script::parser::parser::parser (mu::core::errors::error_target & errors_a, boost::function <void (mu::script::ast::cluster *)> target_a, mu::script::parser_scope::node * scope_a):
errors (errors_a),
target (target_a),
scope (scope_a)
{
    state.push (new (GC) mu::script::parser::cluster (*this));
}

void mu::script::parser::parser::operator () (mu::io::tokens::token const & token_a)
{
    mu::script::parser::state & item (*state.top ());
    item (token_a);
}