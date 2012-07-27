#include <mu/core/errors/error_list.h>
#include <mu/llvm_/instructions/trunc.h>
#include <mu/llvm_/constant_int/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/script/context.h>

#include <llvm/LLVMContext.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (llvm_test, instructions_trunc1)
{
	llvm::LLVMContext context;
	auto constant (llvm::ConstantInt::get (llvm::Type::getInt32Ty (context), 0xffffffff, false));
	auto value (new (GC) mu::llvm_::constant_int::node (constant, new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt32Ty (context))));
	auto type (new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt16Ty (context)));
	llvm::Module module (llvm::StringRef (), context);
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::llvm_::instructions::trunc);
	ctx.push (value);
	ctx.push (type);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto inst (dynamic_cast <mu::llvm_::instruction::node *> (ctx.working (0)));
	EXPECT_NE (inst, nullptr);
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage));
	module.getFunctionList ().push_back (function);
	auto block (llvm::BasicBlock::Create (context));
	function->getBasicBlockList ().push_back (block);
	block->getInstList ().push_back (inst->instruction ());
}
