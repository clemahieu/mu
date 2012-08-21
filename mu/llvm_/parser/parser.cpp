#include <mu/llvm_/parser/parser.h>

#include <mu/llvm_/parser/state.h>
#include <mu/llvm_/parser/cluster.h>

#include <gc_cpp.h>

mu::llvm_::parser::parser::parser (mu::llvm_::ctx & ctx_a, mu::core::errors::error_target & errors_a, boost::function <void (mu::llvm_::ast::cluster *)> target_a):
errors (errors_a),
target (target_a),
ctx (ctx_a)
{
    state.push (new (GC) mu::llvm_::parser::cluster (*this));
}

void mu::llvm_::parser::parser::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    mu::llvm_::parser::state & item (*state.top ());
    item (token_a, context_a);
}