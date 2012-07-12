#include <mu/llvm_/module/get_package.h>
#include <mu/llvm_/function/node.h>
#include <mu/core/errors/error_list.h>
#include <mu/llvm_/module/node.h>
#include <mu/script/package/node.h>
#include <mu/script/astring/node.h>
#include <mu/script/context.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>

#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

TEST (llvm_test, module_get_package1)
{
	llvm::LLVMContext context;
	auto module (boost::shared_ptr <mu::llvm_::module::node> (new mu::llvm_::module::node (new llvm::Module (llvm::StringRef ("test"), context))));	
	std::vector <llvm::Type *> types;
	auto function1 (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), types, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "a"));
	module->module->getFunctionList ().push_back (function1);
	auto function2 (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), types, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "b"));
	module->module->getFunctionList ().push_back (function2);
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::llvm_::module::get_package> ());
	ctx.push (module);
	ctx.push (boost::shared_ptr <mu::script::astring::node> (new mu::script::astring::node (std::string (".suffix"))));
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
	auto package (boost::dynamic_pointer_cast <mu::script::package::node> (ctx.working (0)));
	assert (package.get () != nullptr);
	assert (package->items.size () == 2);
	assert (package->items.find (L"a") != package->items.end ());
	auto f1 (boost::dynamic_pointer_cast <mu::llvm_::function::node> (package->items.find (L"a")->second));
	assert (f1.get () != nullptr);
	assert (f1->value () == function1);
	assert (function1->getNameStr () == std::string ("a.suffix"));
	assert (package->items.find (L"b") != package->items.end ());
	auto f2 (boost::dynamic_pointer_cast <mu::llvm_::function::node> (package->items.find (L"b")->second));
	assert (f2.get () != nullptr);
	assert (f2->value () == function2);
	assert (function2->getNameStr () == std::string ("b.suffix"));
}