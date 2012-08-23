#include <mu/llvm_/synthesizer_routine.h>

#include <mu/llvm_/synthesizer_expression.h>
#include <mu/llvm_/ast_routine.h>
#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/function/node.h>
#include <mu/llvm_/synthesizer_cluster.h>
#include <mu/llvm_/ctx.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/llvm_/context/node.h>

#include <llvm/Module.h>

#include <gc_cpp.h>

mu::llvm_::synthesizer::routine::routine (mu::llvm_::synthesizer::cluster & cluster_a, mu::llvm_::context::node * context_a, mu::llvm_::module::node * module_a, mu::core::errors::error_target & errors_a, mu::llvm_::ast::routine * routine_a)
{
    assert (cluster_a.routines.find (routine_a) == cluster_a.routines.end ());
    auto type (new (GC) mu::llvm_::function_type::node (context_a, routine_a->types, routine_a->results));
    auto function (new (GC) mu::llvm_::function::node (llvm::Function::Create(type->function_type (), llvm::GlobalVariable::ExternalLinkage), type));
    cluster_a.routines [routine_a] = function;
    auto block (new (GC) mu::llvm_::basic_block::node (llvm::BasicBlock::Create(*context_a->context)));
    mu::llvm_::ctx ctx (context_a, module_a, function, block, errors_a);
    mu::llvm_::synthesizer::expression expression (ctx, errors_a, *this, routine_a->body);
}