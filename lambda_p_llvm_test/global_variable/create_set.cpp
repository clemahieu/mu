#include "create_set.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm/global_variable/create_set.h>
#include <lambda_p_llvm/constant_int/node.h>
#include <lambda_p_llvm/integer_type/node.h>
#include <lambda_p_llvm/global_variable/node.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/module/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

void lambda_p_llvm_test::global_variable::create_set::run ()
{
	run_1 ();
}

void lambda_p_llvm_test::global_variable::create_set::run_1 ()
{
	llvm::LLVMContext context;
	auto errors (boost::make_shared <lambda_p::errors::error_list> ());
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (), context)));
	std::vector <boost::shared_ptr <lambda_p::node>> a1;
	a1.push_back (module);
	a1.push_back (boost::make_shared <lambda_p_llvm::constant_int::node> (llvm::ConstantInt::get (llvm::Type::getInt1Ty (context), 0, false), boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context))));
	std::vector <boost::shared_ptr <lambda_p::node>> r1;
	lambda_p_llvm::global_variable::create_set create;
	create.perform (errors, a1, r1);
	assert (errors->errors.empty ());
	assert (r1.size () == 1);
	auto result (boost::dynamic_pointer_cast <lambda_p_llvm::global_variable::node> (r1 [0]));
	assert (result.get () != nullptr);
	auto type (boost::dynamic_pointer_cast <lambda_p_llvm::pointer_type::node> (result->type));
	assert (type.get () != nullptr);
	auto element_type (boost::dynamic_pointer_cast <lambda_p_llvm::integer_type::node> (type->element));
	assert (element_type.get () != nullptr);
}