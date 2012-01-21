#include "get_package.h"

#include <lambda_p_llvm_wrapper/module/get_package.h>
#include <lambda_p_llvm_wrapper/function/node.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm_wrapper/module/node.h>
#include <lambda_p_script/package/node.h>
#include <lambda_p_script/astring/node.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>

void lambda_p_llvm_wrapper_test::module::get_package::run ()
{
	run_1 ();
}

void lambda_p_llvm_wrapper_test::module::get_package::run_1 ()
{
	llvm::LLVMContext context;
	auto module (boost::shared_ptr <lambda_p_llvm_wrapper::module::node> (new lambda_p_llvm_wrapper::module::node (new llvm::Module (llvm::StringRef ("test"), context))));	
	std::vector <llvm::Type *> types;
	auto function1 (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), types, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "a"));
	module->module->getFunctionList ().push_back (function1);
	auto function2 (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), types, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "b"));
	module->module->getFunctionList ().push_back (function2);
	lambda_p_llvm_wrapper::module::get_package get;
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	arguments.push_back (module);
	arguments.push_back (boost::shared_ptr <lambda_p_script::astring::node> (new lambda_p_script::astring::node (std::string (".suffix"))));
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	get.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto package (boost::dynamic_pointer_cast <lambda_p_script::package::node> (results [0]));
	assert (package.get () != nullptr);
	assert (package->items.size () == 2);
	assert (package->items.find (L"a") != package->items.end ());
	auto f1 (boost::dynamic_pointer_cast <lambda_p_llvm_wrapper::function::node> (package->items.find (L"a")->second));
	assert (f1.get () != nullptr);
	assert (f1->function () == function1);
	assert (function1->getNameStr () == std::string ("a.suffix"));
	assert (package->items.find (L"b") != package->items.end ());
	auto f2 (boost::dynamic_pointer_cast <lambda_p_llvm_wrapper::function::node> (package->items.find (L"b")->second));
	assert (f2.get () != nullptr);
	assert (f2->function () == function2);
	assert (function2->getNameStr () == std::string ("b.suffix"));
}