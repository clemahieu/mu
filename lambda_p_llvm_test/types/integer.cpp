#include "integer.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm/types/integer.h>
#include <lambda_p_llvm/apint/node.h>

#include <llvm/LLVMContext.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>

#include <boost/make_shared.hpp>

#include <vector>

void lambda_p_llvm_test::types::integer::run ()
{
	run_1 ();
}

void lambda_p_llvm_test::types::integer::run_1 ()
{
	lambda_p_llvm::types::integer integer;
	llvm::LLVMContext context;
	auto block (llvm::BasicBlock::Create (context));
	auto errors (boost::make_shared <lambda_p::errors::error_list> ());
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	arguments.push_back (boost::make_shared <lambda_p_llvm::apint::node> (new llvm::APInt (64, 16)));
	integer (errors, block, arguments, results);
	assert (errors->errors.empty ());
}