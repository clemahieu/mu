#include <mu/core/errors/error_list.h>
#include <mu/llvm_/function_type_create.h>
#include <mu/llvm_/function_type_node.h>
#include <mu/llvm_/context_node.h>
#include <mu/script/values_operation.h>
#include <mu/llvm_/integer_type_node.h>
#include <mu/llvm_/set_type_node.h>
#include <mu/script/context.h>
#include <mu/llvm_/function_type_divider.h>

#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (llvm_test, function_type_create1)
{
	llvm::LLVMContext context_l;
	auto context (new (GC) mu::llvm_::context::node (&context_l));
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::llvm_::function_type::create);
	ctx.push (context);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto type (dynamic_cast <mu::llvm_::function_type::node *> (ctx.working (0)));
	EXPECT_NE (type, nullptr);
	EXPECT_EQ (type->parameters.size (), 0);
	auto return_type (type->function_type ()->getReturnType ());
	EXPECT_EQ (return_type, llvm::Type::getVoidTy (context_l));
	EXPECT_EQ (type->function_type ()->getNumParams (), 0);
}

TEST (llvm_test, function_type_create2)
{
	llvm::LLVMContext context_l;
	auto context (new (GC) mu::llvm_::context::node (&context_l));
	mu::llvm_::function_type::create create;
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::llvm_::function_type::create);
	ctx.push (context);
	ctx.push (new (GC) mu::llvm_::integer_type::node (llvm::IntegerType::get (context_l, 1)));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto type (dynamic_cast <mu::llvm_::function_type::node *> (ctx.working (0)));
	EXPECT_NE (type, nullptr);
	EXPECT_EQ (type->parameters.size (), 1);
	auto return_type (type->function_type ()->getReturnType ());
	EXPECT_EQ (return_type, llvm::Type::getVoidTy (context_l));
	EXPECT_EQ (type->function_type ()->getNumParams (), 1);
	auto arg1 (type->function_type ()->getParamType (0));
	EXPECT_EQ (arg1, llvm::Type::getInt1Ty (context_l));
}

TEST (llvm_test, function_type_create3)
{
	llvm::LLVMContext context_l;
	auto context (new (GC) mu::llvm_::context::node (&context_l));
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::llvm_::function_type::create);
	ctx.push (context);
	ctx.push (new (GC) mu::llvm_::integer_type::node (llvm::IntegerType::get (context_l, 1)));
	ctx.push (new (GC) mu::llvm_::integer_type::node (llvm::IntegerType::get (context_l, 8)));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto type (dynamic_cast <mu::llvm_::function_type::node *> (ctx.working (0)));
	EXPECT_NE (type, nullptr);
	EXPECT_EQ (type->parameters.size (), 2);
	auto return_type (type->function_type ()->getReturnType ());
	EXPECT_EQ (return_type, llvm::Type::getVoidTy (context_l));
	EXPECT_EQ (type->function_type ()->getNumParams (), 2);
	auto arg1 (type->function_type ()->getParamType (0));
	EXPECT_EQ (arg1, llvm::Type::getInt1Ty (context_l));
	auto arg2 (type->function_type ()->getParamType (1));
	EXPECT_EQ (arg2, llvm::Type::getInt8Ty (context_l));
}

TEST (llvm_test, function_type_create4)
{
	llvm::LLVMContext context_l;
	auto context (new (GC) mu::llvm_::context::node (&context_l));
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::llvm_::function_type::create);
	ctx.push (context);
	ctx.push (new (GC) mu::llvm_::function_type::divider);
	ctx.push (new (GC) mu::llvm_::integer_type::node (llvm::IntegerType::get (context_l, 1)));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto type (dynamic_cast <mu::llvm_::function_type::node *> (ctx.working (0)));
	EXPECT_NE (type, nullptr);
	EXPECT_EQ (type->function_type ()->getNumParams (), 0);
	auto return_type (type->function_type ()->getReturnType ());
	EXPECT_EQ (return_type, llvm::Type::getInt1Ty (context_l));
}

TEST (llvm_test, function_type_create5)
{
	llvm::LLVMContext context_l;
	auto context (new (GC) mu::llvm_::context::node (&context_l));
	mu::llvm_::function_type::create create;
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::llvm_::function_type::create);
	ctx.push (context);
	ctx.push (new (GC) mu::llvm_::function_type::divider);
	ctx.push (new (GC) mu::llvm_::integer_type::node (llvm::IntegerType::get (context_l, 1)));
	ctx.push (new (GC) mu::llvm_::integer_type::node (llvm::IntegerType::get (context_l, 8)));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto type (dynamic_cast <mu::llvm_::function_type::node *> (ctx.working (0)));
	EXPECT_NE (type, nullptr);
	EXPECT_EQ (type->function_type ()->getNumParams (), 0);
	auto return_type (dynamic_cast <mu::llvm_::set_type::node *> (type->output));
	EXPECT_EQ (return_type->elements.size (), 2);
	EXPECT_EQ (return_type->elements [0]->type (), llvm::Type::getInt1Ty (context_l));
	EXPECT_EQ (return_type->elements [1]->type (), llvm::Type::getInt8Ty (context_l));
	auto struct_type (llvm::dyn_cast <llvm::StructType> (return_type->type ()));
	EXPECT_NE (struct_type, nullptr);
	EXPECT_EQ (struct_type->getNumElements (), 2);
	EXPECT_EQ (struct_type->getElementType (0), llvm::Type::getInt1Ty (context_l));
	EXPECT_EQ (struct_type->getElementType (1), llvm::Type::getInt8Ty (context_l));
}