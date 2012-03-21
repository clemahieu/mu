#include <mu/llvm_test/function/create.h>

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/function/create.h>
#include <mu/llvm_/function/node.h>
#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/type/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/DerivedTypes.h>

void mu::llvm_test::function::create::run ()
{
	run_1 ();
}

void mu::llvm_test::function::create::run_1 ()
{
	llvm::LLVMContext context;
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::llvm_::function::create> ());
	ctx.push (boost::make_shared <mu::llvm_::function_type::node> (boost::make_shared <mu::llvm_::context::node> (&context), llvm::FunctionType::get (llvm::Type::getVoidTy (context), false)));
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
	auto function (boost::dynamic_pointer_cast <mu::llvm_::function::node> (ctx.working (0)));
	assert (function.get () != nullptr);
	auto ptr (boost::dynamic_pointer_cast <mu::llvm_::pointer_type::node> (function->type));
	assert (ptr.get () != nullptr);
}