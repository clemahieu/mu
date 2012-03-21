#include <mu/llvm_test/types/integer.h>

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
	llvm::LLVMContext context;
	auto block (llvm::BasicBlock::Create (context));
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context ctx;
	ctx.push (boost::make_shared <mu::llvm_::integer_type::create> ());
	ctx.push (boost::make_shared <mu::llvm_::context::node> (&context));
	ctx.push (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, 16)));
	auto valid (ctx ());
	assert (valid);
}