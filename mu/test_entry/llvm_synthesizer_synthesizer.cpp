#include <mu/llvm_/synthesizer_synthesizer.h>
#include <mu/core/errors/error_list.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/ast_cluster.h>
#include <mu/llvm_/ast_routine.h>
#include <mu/llvm_/ast_expression.h>
#include <mu/llvm_/ast_reference.h>
#include <mu/llvm_/ast_parameter.h>
#include <mu/llvm_/cluster/node.h>
#include <mu/llvm_/identity/operation.h>
#include <mu/llvm_/function/node.h>

#include <llvm/LLVMContext.h>
#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

// Empty construction
TEST (llvm_test, synthesizer1)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext ctx;
    mu::llvm_::context::node context (&ctx);
    mu::vector <mu::llvm_::cluster::node *> clusters;
    mu::llvm_::synthesizer::synthesizer synthesizer (&context, errors,
                                                     [&clusters]
                                                     (mu::llvm_::cluster::node * cluster_a)
                                                     {
                                                         clusters.push_back (cluster_a);
                                                     });
    ASSERT_TRUE (clusters.size () == 0);
}

// Empty cluster
TEST (llvm_test, synthesizer2)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext ctx;
    mu::llvm_::context::node context (&ctx);
    mu::vector <mu::llvm_::cluster::node *> clusters;
    mu::llvm_::synthesizer::synthesizer synthesizer (&context, errors,
                                                     [&clusters]
                                                     (mu::llvm_::cluster::node * cluster_a)
                                                     {
                                                         clusters.push_back (cluster_a);
                                                     });
    auto cluster1 (new (GC) mu::llvm_::ast::cluster);
    synthesizer (cluster1);
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster2 (clusters [0]);
    ASSERT_TRUE (cluster2->routines.size () == 0);
}

// Routine empty body
TEST (llvm_test, synthesizer3)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext ctx;
    mu::llvm_::context::node context (&ctx);
    mu::vector <mu::llvm_::cluster::node *> clusters;
    mu::llvm_::synthesizer::synthesizer synthesizer (&context, errors,
                                                     [&clusters]
                                                     (mu::llvm_::cluster::node * cluster_a)
                                                     {
                                                         clusters.push_back (cluster_a);
                                                     });
    auto cluster1 (new (GC) mu::llvm_::ast::cluster);
    auto routine1 (new (GC) mu::llvm_::ast::routine);
    cluster1->routines.push_back (routine1);
    routine1->body->nodes.nodes.push_back (new (GC) mu::llvm_::identity::operation);
    synthesizer (cluster1);
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster2 (clusters [0]);
    ASSERT_TRUE (cluster2->routines.size () == 1);
    auto routine2 (cluster2->routines [0]);
    auto function (routine2->function ());
    auto type (function->getFunctionType ());
    EXPECT_TRUE (type->getReturnType ()->isVoidTy ());
    EXPECT_TRUE (type->getNumParams () == 0);
    ASSERT_TRUE (function->getBasicBlockList ().size () == 1);
    auto block (function->getBasicBlockList ().begin ());
    ASSERT_TRUE (block->getInstList ().size () == 1);
    auto instruction (block->getInstList ().begin ());
    ASSERT_TRUE (llvm::dyn_cast <llvm::ReturnInst> (instruction) != nullptr);
}