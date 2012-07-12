#include <mu/llvm_/module/node.h>
#include <mu/llvm_/module/get_package.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/astring/node.h>
#include <mu/llvm_/module/add_package.h>
#include <mu/script/context.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

TEST (llvm_test, module_add_package1)
{	
	llvm::LLVMContext context;
	auto module (boost::shared_ptr <mu::llvm_::module::node> (new mu::llvm_::module::node (new llvm::Module (llvm::StringRef ("test"), context))));	
	std::vector <llvm::Type *> types;
	auto function1 (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), types, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "a"));
	function1->getBasicBlockList ().push_back (llvm::BasicBlock::Create (context));
	assert (!function1->isDeclaration ());
	module->module->getFunctionList ().push_back (function1);
	auto function2 (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), types, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "b"));
	function2->getBasicBlockList ().push_back (llvm::BasicBlock::Create (context));
	assert (!function2->isDeclaration ());
	module->module->getFunctionList ().push_back (function2);
	mu::llvm_::module::get_package get;
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::llvm_::module::get_package> ());
	ctx.push (module);
	ctx.push (boost::make_shared <mu::script::astring::node> (std::string (".suffix")));
	auto valid (ctx ());
	assert (valid);
	auto mod1 (boost::shared_ptr <mu::llvm_::module::node> (new mu::llvm_::module::node (new llvm::Module (llvm::StringRef ("test"), context))));
	ctx.slide ();
	ctx.push (boost::make_shared <mu::llvm_::module::add_package> ());
	ctx.push (mod1);
	ctx.push (ctx.locals (0));
	auto valid2 (ctx ());
	assert (valid2);
	assert (ctx.working_size () == 0);
	assert (mod1->module->getFunctionList ().size () == 2);
	auto fn1 (mod1->module->getFunction ("a.suffix"));
	assert (fn1 != nullptr);
	assert (fn1->getType () == function1->getType ());
	assert (fn1->isDeclaration ());
	auto fn2 (mod1->module->getFunction ("b.suffix"));
	assert (fn2 != nullptr);
	assert (fn2->getType () == function2->getType ());
	assert (fn2->isDeclaration ());
}