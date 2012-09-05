#include <mu/llvm_/parser_parser.h>

#include <mu/llvm_/parser_state.h>
#include <mu/llvm_/parser_cluster.h>

#include <gc_cpp.h>

mu::llvm_::parser::parser::parser (mu::llvm_::context::node * ctx_a, mu::core::errors::error_target & errors_a, boost::function <void (mu::llvm_::ast::cluster *)> target_a):
errors (errors_a),
target (target_a)
{
    state.push (new (GC) mu::llvm_::parser::cluster (*this));
}

void mu::llvm_::parser::parser::operator () (mu::io::tokens::token * token_a)
{
    mu::llvm_::parser::state & item (*state.top ());
    item (token_a);
}