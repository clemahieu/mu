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

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (llvm_test, function_create1)
{
	llvm::LLVMContext context;
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
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