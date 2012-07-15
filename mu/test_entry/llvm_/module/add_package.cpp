#include <mu/llvm_/module/node.h>
#include <mu/llvm_/module/get_package.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/astring/node.h>
#include <mu/llvm_/module/add_package.h>
#include <mu/script/context.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (llvm_test, module_add_package1)
{	
	llvm::LLVMContext context;
	auto module (new (GC) mu::llvm_::module::node (new llvm::Module (llvm::StringRef ("test"), context)));	
	std::vector <llvm::Type *> types;
	auto function1 (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), types, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "a"));
	function1->getBasicBlockList ().push_back (llvm::BasicBlock::Create (context));
	EXPECT_EQ (!function1->isDeclaration (), true);
	module->module->getFunctionList ().push_back (function1);
	auto function2 (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), types, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "b"));
	function2->getBasicBlockList ().push_back (llvm::BasicBlock::Create (context));
	EXPECT_EQ (!function2->isDeclaration (), true);
	module->module->getFunctionList ().push_back (function2);
	mu::llvm_::module::get_package get;
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::llvm_::module::get_package);
	ctx.push (module);
	ctx.push (new (GC) mu::script::astring::node (std::string (".suffix")));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	auto mod1 (new (GC) mu::llvm_::module::node (new llvm::Module (llvm::StringRef ("test"), context)));
	ctx.slide ();
	ctx.push (new (GC) mu::llvm_::module::add_package);
	ctx.push (mod1);
	ctx.push (ctx.locals (0));
	auto valid2 (ctx ());
	EXPECT_EQ (valid2, true);
	EXPECT_EQ (ctx.working_size (), 0);
	EXPECT_EQ (mod1->module->getFunctionList ().size (), 2);
	auto fn1 (mod1->module->getFunction ("a.suffix"));
	EXPECT_NE (fn1, nullptr);
	EXPECT_EQ (fn1->getType (), function1->getType ());
	EXPECT_EQ (fn1->isDeclaration (), true);
	auto fn2 (mod1->module->getFunction ("b.suffix"));
	EXPECT_NE (fn2, nullptr);
	EXPECT_EQ (fn2->getType (), function2->getType ());
	EXPECT_EQ (fn2->isDeclaration (), true);
}