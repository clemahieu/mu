#include "create.h"

#include <mu/core/errors/error_list.h>
#include <lambda_p_llvm/function/create.h>
#include <lambda_p_llvm/function/node.h>
#include <lambda_p_llvm/function_type/node.h>
#include <lambda_p_llvm/type/node.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/context/node.h>

#include <boost/make_shared.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/DerivedTypes.h>

void lambda_p_llvm_test::function::create::run ()
{
	run_1 ();
}

void lambda_p_llvm_test::function::create::run_1 ()
{
	llvm::LLVMContext context;
	lambda_p_llvm::function::create create;
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	a1.push_back (boost::make_shared <lambda_p_llvm::function_type::node> (boost::make_shared <lambda_p_llvm::context::node> (&context), llvm::FunctionType::get (llvm::Type::getVoidTy (context), false)));
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	create (errors, a1, r1);
	assert (errors->errors.empty ());
	assert (r1.size () == 1);
	auto function (boost::dynamic_pointer_cast <lambda_p_llvm::function::node> (r1 [0]));
	assert (function.get () != nullptr);
	auto ptr (boost::dynamic_pointer_cast <lambda_p_llvm::pointer_type::node> (function->type));
	assert (ptr.get () != nullptr);
}