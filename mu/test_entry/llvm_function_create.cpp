#include <mu/core/errors/error_list.h>
#include <mu/llvm_/function_create.h>
#include <mu/llvm_/function_node.h>
#include <mu/llvm_/function_type_node.h>
#include <mu/llvm_/type_node.h>
#include <mu/llvm_/pointer_type_node.h>
#include <mu/llvm_/context_node.h>
#include <mu/script/context.h>

#include <llvm/LLVMContext.h>
#include <llvm/DerivedTypes.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (llvm_test, function_create1)
{
	llvm::LLVMContext context;
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::llvm_::function::create);
	ctx.push (new (GC) mu::llvm_::function_type::node (new (GC) mu::llvm_::context::node (&context), llvm::FunctionType::get (llvm::Type::getVoidTy (context), false)));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto function (dynamic_cast <mu::llvm_::function::node *> (ctx.working (0)));
	EXPECT_NE (function, nullptr);
	auto ptr (dynamic_cast <mu::llvm_::pointer_type::node *> (function->type));
	EXPECT_NE (ptr, nullptr);
}