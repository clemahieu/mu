#include "create.h"

#include <core/errors/error_list.h>
#include <lambda_p_llvm/constant_string/create.h>
#include <lambda_p_script/string/node.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_llvm/global_variable/node.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/integer_type/node.h>

#include <boost/make_shared.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>

void lambda_p_llvm_test::constant_string::create::run ()
{
	run_1 ();
}

void lambda_p_llvm_test::constant_string::create::run_1 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	llvm::LLVMContext context;
	auto module (new llvm::Module (llvm::StringRef (), context));
	a1.push_back (boost::make_shared <lambda_p_llvm::context::node> (&context));
	a1.push_back (boost::make_shared <lambda_p_llvm::module::node> (module));
	a1.push_back (boost::make_shared <lambda_p_script::string::node> (std::wstring (L"test string")));
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	lambda_p_llvm::constant_string::create create;
	create.perform (errors, a1, r1);
	assert (errors->errors.empty ());
	assert (r1.size () == 1);
	auto result (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (r1 [0]));
	assert (result.get () != nullptr);
	//assert (result->global_variable ()->isConstant ());
	//assert (result->global_variable ()->hasInitializer ());
	//auto initializer (result->global_variable ()->getInitializer ());
	//assert (initializer != nullptr);
	//auto array (llvm::cast <llvm::ConstantArray> (initializer));
	//assert (array != nullptr);
	//auto elements (array->getType ()->getNumElements ());
	//assert (elements == 11);
	auto type (boost::dynamic_pointer_cast <lambda_p_llvm::pointer_type::node> (result->type));
	assert (type.get () != nullptr);
	auto element_type (boost::dynamic_pointer_cast <lambda_p_llvm::integer_type::node> (type->element));
	assert (element_type.get () != nullptr);
}