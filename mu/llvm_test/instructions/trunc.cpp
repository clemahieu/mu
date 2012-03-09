#include <mu/llvm_test/instructions/trunc.h>

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/instructions/trunc.h>
#include <mu/llvm_/constant_int/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/llvm_/instruction/node.h>

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
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	llvm::Module module (llvm::StringRef (), context);
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	a1.push_back (value);
	a1.push_back (type);
	mu::llvm_::instructions::trunc trunc;
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	auto ctx (mu::script::context (errors, a1, r1));
	trunc.perform (ctx);
	assert (errors->errors.empty ());
	assert (r1.size () == 1);
	auto inst (boost::dynamic_pointer_cast <mu::llvm_::instruction::node> (r1 [0]));
	assert (inst.get () != nullptr);
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage));
	module.getFunctionList ().push_back (function);
	auto block (llvm::BasicBlock::Create (context));
	function->getBasicBlockList ().push_back (block);
	block->getInstList ().push_back (inst->instruction ());
}
