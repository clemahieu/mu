#include "insert.h"

#include <lambda_p_llvm/basic_block/node.h>
#include <lambda_p_llvm/instruction/node.h>
#include <lambda_p_llvm/basic_block/insert.h>
#include <core/errors/error_list.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/integer_type/node.h>

#include <boost/make_shared.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>
#include <llvm/Function.h>
#include <llvm/Module.h>

void lambda_p_llvm_test::basic_block::insert::run ()
{
	run_1 ();
}

void lambda_p_llvm_test::basic_block::insert::run_1 ()
{
	llvm::LLVMContext context;
	auto module (new llvm::Module (llvm::StringRef (), context));
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage));
	module->getFunctionList ().push_back (function);
	auto block (boost::make_shared <lambda_p_llvm::basic_block::node> (llvm::BasicBlock::Create (context)));
	function->getBasicBlockList ().push_back (block->block);
	auto instruction (boost::make_shared <lambda_p_llvm::instruction::node> (new llvm::AllocaInst (llvm::Type::getInt1Ty (context)), boost::make_shared <lambda_p_llvm::pointer_type::node> (boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context)))));
	lambda_p_llvm::basic_block::insert insert;
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	arguments.push_back (block);
	arguments.push_back (instruction);
	insert (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (block->block->getInstList ().size () == 1);
}