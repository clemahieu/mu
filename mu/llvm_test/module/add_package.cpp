#include "add_package.h"

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

void mu::llvm_test::module::add_package::run ()
{
	run_1 ();
}

void mu::llvm_test::module::add_package::run_1 ()
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
	boost::shared_ptr <mu::core::errors::error_list> errors (new mu::core::errors::error_list);
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	arguments.push_back (module);
	arguments.push_back (boost::shared_ptr <mu::script::astring::node> (new mu::script::astring::node (std::string (".suffix"))));
	std::vector <boost::shared_ptr <mu::core::node>> results;
	std::vector <std::type_info const *> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	get (ctx);
	assert (errors->errors.empty ());
	auto mod1 (boost::shared_ptr <mu::llvm_::module::node> (new mu::llvm_::module::node (new llvm::Module (llvm::StringRef ("test"), context))));
	std::vector <boost::shared_ptr <mu::core::node>> args1;
	args1.push_back (mod1);
	args1.push_back (results [0]);
	std::vector <boost::shared_ptr <mu::core::node>> res1;
	mu::llvm_::module::add_package add;
	std::vector <std::type_info const *> stack2;
    auto ctx2 (mu::script::context (errors, args1, res1, stack2));
	add (ctx2);
	assert (errors->errors.empty ());
	assert (res1.empty ());
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