#include <mu/llvm_test/instructions/trunc.h>

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/instructions/trunc.h>
#include <mu/llvm_/constant_int/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>

void mu::llvm_test::instructions::trunc::run ()
{
	run_1 ();
}

void mu::llvm_test::instructions::trunc::run_1 ()
{
	llvm::LLVMContext context;
	auto constant (llvm::ConstantInt::get (llvm::Type::getInt32Ty (context), 0xffffffff, false));
	auto value (boost::make_shared <mu::llvm_::constant_int::node> (constant, boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt32Ty (context))));
	auto type (boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt16Ty (context)));
	llvm::Module module (llvm::StringRef (), context);
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::llvm_::instructions::trunc> ());
	ctx.push (value);
	ctx.push (type);
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
	auto inst (boost::dynamic_pointer_cast <mu::llvm_::instruction::node> (ctx.working (0)));
	assert (inst.get () != nullptr);
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage));
	module.getFunctionList ().push_back (function);
	auto block (llvm::BasicBlock::Create (context));
	function->getBasicBlockList ().push_back (block);
	block->getInstList ().push_back (inst->instruction ());
}
