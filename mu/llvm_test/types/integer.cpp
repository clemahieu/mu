#include "integer.h"

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/apint/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/integer_type/create.h>
#include <mu/script/context.h>

#include <llvm/LLVMContext.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>

#include <boost/make_shared.hpp>

#include <vector>

void mu::llvm_test::types::integer::run ()
{
	run_1 ();
}

void mu::llvm_test::types::integer::run_1 ()
{
	mu::llvm_::integer_type::create integer;
	llvm::LLVMContext context;
	auto block (llvm::BasicBlock::Create (context));
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	arguments.push_back (boost::make_shared <mu::llvm_::context::node> (&context));
	arguments.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, 16)));
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	integer (ctx);
	assert (errors->errors.empty ());
}