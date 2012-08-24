#include <mu/llvm_/synthesizer_synthesizer.h>
#include <mu/core/errors/error_list.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/ast_cluster.h>
#include <mu/llvm_/ast_routine.h>
#include <mu/llvm_/ast_expression.h>
#include <mu/llvm_/ast_reference.h>
#include <mu/llvm_/ast_parameter.h>
#include <mu/llvm_/cluster/node.h>

#include <llvm/LLVMContext.h>

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
    synthesizer (cluster1);
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster2 (clusters [0]);
    ASSERT_TRUE (cluster2->routines.size () == 0);
}