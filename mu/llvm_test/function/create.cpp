#include "create.h"

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
	mu::llvm_::function::create create;
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	a1.push_back (boost::make_shared <mu::llvm_::function_type::node> (boost::make_shared <mu::llvm_::context::node> (&context), llvm::FunctionType::get (llvm::Type::getVoidTy (context), false)));
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	std::vector <std::type_info const *> stack;
	std::vector <mu::core::context> context_stack;
    auto ctx (mu::script::context (errors, a1, r1, stack, context_stack));
	create (ctx);
	assert (errors->errors.empty ());
	assert (r1.size () == 1);
	auto function (boost::dynamic_pointer_cast <mu::llvm_::function::node> (r1 [0]));
	assert (function.get () != nullptr);
	auto ptr (boost::dynamic_pointer_cast <mu::llvm_::pointer_type::node> (function->type));
	assert (ptr.get () != nullptr);
}