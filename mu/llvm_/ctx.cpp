#include <mu/llvm_/ctx.h>

mu::llvm_::ctx::ctx (mu::llvm_::context::node * context_a, mu::llvm_::module::node * module_a, mu::llvm_::function::node * function_a, mu::llvm_::basic_block::node * block_a, mu::core::errors::error_target & errors_a):
context (context_a),
module (module_a),
function (function_a),
block (block_a),
errors (errors_a)
{
}