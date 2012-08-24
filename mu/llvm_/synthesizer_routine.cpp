#include <mu/llvm_/synthesizer_routine.h>

#include <mu/llvm_/synthesizer_expression.h>
#include <mu/llvm_/ast_routine.h>
#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/function/node.h>
#include <mu/llvm_/synthesizer_cluster.h>
#include <mu/llvm_/ctx.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/core/errors/error_target.h>

#include <llvm/Module.h>
#include <llvm/Instructions.h>

#include <gc_cpp.h>

mu::llvm_::synthesizer::routine::routine (mu::llvm_::synthesizer::cluster & cluster_a, mu::llvm_::context::node * context_a, mu::llvm_::module::node * module_a, mu::core::errors::error_target & errors_a, mu::llvm_::ast::routine * routine_a)
{
    assert (cluster_a.routines.find (routine_a) == cluster_a.routines.end ());
    auto type (new (GC) mu::llvm_::function_type::node (context_a, routine_a->types, routine_a->results));
    auto function (new (GC) mu::llvm_::function::node (llvm::Function::Create(type->function_type (), llvm::GlobalVariable::ExternalLinkage), type));
    routine_m = function;
    cluster_a.routines [routine_a] = function;
    auto block (new (GC) mu::llvm_::basic_block::node (llvm::BasicBlock::Create(*context_a->context)));
    function->function ()->getBasicBlockList ().push_back (block->block);
    mu::llvm_::ctx ctx (context_a, module_a, function, block, errors_a);
    mu::llvm_::synthesizer::expression expression (ctx, errors_a, *this, routine_a->body);
    if (ctx.working.size () == 0)
    {
        ctx.block->block->getInstList ().push_back (llvm::ReturnInst::Create (*context_a->context));
    }
    else if (ctx.working.size () == 1)
    {
        auto value (dynamic_cast <mu::llvm_::value::node *> (ctx.working [0]));
        if (value != nullptr)
        {
            llvm::ReturnInst::Create (*ctx.context->context, value->value (), ctx.block->block);
        }
        else
        {
            errors_a (U"Function is not returning an llvm::value::node");
        }
    }
    else
    {
        assert (false);
    }
}