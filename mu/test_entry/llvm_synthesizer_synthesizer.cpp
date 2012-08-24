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
#include <mu/llvm_/integer_type/node.h>
#include <mu/llvm_/constant_int/node.h>
#include <mu/llvm_/module/node.h>

#include <llvm/LLVMContext.h>
#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/Constants.h>
#include <llvm/Module.h>

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
    auto module (cluster2->module);
    ASSERT_TRUE (module != nullptr);
    ASSERT_TRUE (module->module->getFunctionList ().size () == 0);
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
    auto module (cluster2->module);
    ASSERT_TRUE (module != nullptr);
    ASSERT_TRUE (module->module->getFunctionList ().size () == 1);
    auto functions (module->module->getFunctionList ().begin ());
    EXPECT_TRUE (function == functions);
    auto type (function->getFunctionType ());
    EXPECT_TRUE (type->getReturnType ()->isVoidTy ());
    EXPECT_TRUE (type->getNumParams () == 0);
    ASSERT_TRUE (function->getBasicBlockList ().size () == 1);
    auto block (function->getBasicBlockList ().begin ());
    ASSERT_TRUE (block->getInstList ().size () == 1);
    auto instruction (block->getInstList ().begin ());
    ASSERT_TRUE (llvm::isa <llvm::ReturnInst> (instruction));
}

// i32 parameter
TEST (llvm_test, synthesizer4)
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
    routine1->types.push_back (new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt32Ty (ctx)));
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
    ASSERT_TRUE (type->getNumParams () == 1);
    auto p1 (type->getParamType (0));
    ASSERT_TRUE (p1->isIntegerTy (32));
    ASSERT_TRUE (function->getBasicBlockList ().size () == 1);
    auto block (function->getBasicBlockList ().begin ());
    ASSERT_TRUE (block->getInstList ().size () == 1);
    auto instruction (block->getInstList ().begin ());
    ASSERT_TRUE (llvm::isa <llvm::ReturnInst> (instruction));
}

// Return single value
TEST (llvm_test, synthesizer5)
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
    auto return_type (new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (ctx)));
    auto const1 (new (GC) mu::llvm_::constant_int::node (llvm::ConstantInt::getTrue (ctx), return_type));
    routine1->body->nodes.nodes.push_back (const1);
    routine1->results.push_back (return_type);
    synthesizer (cluster1);
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster2 (clusters [0]);
    ASSERT_TRUE (cluster2->routines.size () == 1);
    auto routine2 (cluster2->routines [0]);
    auto function (routine2->function ());
    auto type (function->getFunctionType ());
    EXPECT_TRUE (type->getReturnType ()->isIntegerTy (1));
    ASSERT_TRUE (type->getNumParams () == 0);
    ASSERT_TRUE (function->getBasicBlockList ().size () == 1);
    auto block (function->getBasicBlockList ().begin ());
    ASSERT_TRUE (block->getInstList ().size () == 1);
    auto instruction (block->getInstList ().begin ());
    ASSERT_TRUE (llvm::isa <llvm::ReturnInst> (instruction));
    auto ret (llvm::cast <llvm::ReturnInst> (instruction)->getReturnValue ());
    ASSERT_TRUE (ret != nullptr);
    ASSERT_TRUE (ret->getType()->isIntegerTy (1));
    ASSERT_TRUE (ret == const1->value ());
}

// Error, mismatched actual return with empty declared
TEST (llvm_test, synthesizer6)
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
    auto return_type (new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (ctx)));
    auto const1 (new (GC) mu::llvm_::constant_int::node (llvm::ConstantInt::getTrue (ctx), return_type));
    routine1->body->nodes.nodes.push_back (const1);
    synthesizer (cluster1);
    ASSERT_TRUE (errors ());
}

// Error, mismatched actual return with single declared
TEST (llvm_test, synthesizer7)
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
    auto return_type (new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (ctx)));
    routine1->results.push_back (return_type);
    synthesizer (cluster1);
    ASSERT_TRUE (errors ());
}

// Error, mismatched actual return with multiple declared
TEST (llvm_test, synthesizer8)
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
    auto return_type (new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (ctx)));
    auto const1 (new (GC) mu::llvm_::constant_int::node (llvm::ConstantInt::getTrue (ctx), return_type));
    routine1->results.push_back (return_type);
    routine1->results.push_back (return_type);
    routine1->body->nodes.nodes.push_back (const1);
    synthesizer (cluster1);
    ASSERT_TRUE (errors ());
}

// Error, mismatched return types in single return
TEST (llvm_test, synthesizer9)
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
    auto return_type (new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt8Ty (ctx)));
    auto const1 (new (GC) mu::llvm_::constant_int::node (llvm::ConstantInt::getTrue (ctx), new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (ctx))));
    routine1->results.push_back (return_type);
    routine1->body->nodes.nodes.push_back (const1);
    synthesizer (cluster1);
    ASSERT_TRUE (errors ());
}

// Error, mismatched one return type in multiple return
TEST (llvm_test, synthesizer10)
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
    auto return_type1 (new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (ctx)));
    auto return_type2 (new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt8Ty (ctx)));
    auto const1 (new (GC) mu::llvm_::constant_int::node (llvm::ConstantInt::getTrue (ctx), new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (ctx))));
    auto const2 (new (GC) mu::llvm_::constant_int::node (llvm::ConstantInt::getTrue (ctx), new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (ctx))));
    routine1->results.push_back (return_type1);
    routine1->results.push_back (return_type2);
    routine1->body->nodes.nodes.push_back (const1);
    routine1->body->nodes.nodes.push_back (const2);
    synthesizer (cluster1);
    ASSERT_TRUE (errors ());
}

// Return parameter
TEST (llvm_test, synthesizer11)
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
    auto return_type (new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (ctx)));
    routine1->body->nodes.nodes.push_back (new (GC) mu::llvm_::ast::parameter (0));
    routine1->types.push_back (return_type);
    routine1->results.push_back (return_type);
    synthesizer (cluster1);
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster2 (clusters [0]);
    ASSERT_TRUE (cluster2->routines.size () == 1);
    auto routine2 (cluster2->routines [0]);
    auto function (routine2->function ());
    auto type (function->getFunctionType ());
    EXPECT_TRUE (type->getReturnType ()->isIntegerTy (1));
    ASSERT_TRUE (type->getNumParams () == 1);
    ASSERT_TRUE (function->getBasicBlockList ().size () == 1);
    auto block (function->getBasicBlockList ().begin ());
    ASSERT_TRUE (block->getInstList ().size () == 1);
    auto instruction (block->getInstList ().begin ());
    ASSERT_TRUE (llvm::isa <llvm::ReturnInst> (instruction));
    auto ret (llvm::cast <llvm::ReturnInst> (instruction)->getReturnValue ());
    ASSERT_TRUE (ret != nullptr);
    ASSERT_TRUE (ret->getType()->isIntegerTy (1));
    auto value (llvm::cast <llvm::ReturnInst> (instruction)->getReturnValue ());
    ASSERT_TRUE (llvm::isa <llvm::Argument> (value));
    auto argument (llvm::cast <llvm::Argument> (value));
    ASSERT_TRUE (argument->getArgNo () == 0);
}