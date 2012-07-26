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

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (llvm_test, module_get_package1)
{
	llvm::LLVMContext context;
	auto module (new (GC) mu::llvm_::module::node (new llvm::Module (llvm::StringRef ("test"), context)));	
	std::vector <llvm::Type *> types;
	auto function1 (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), types, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "a"));
	module->module->getFunctionList ().push_back (function1);
	auto function2 (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), types, false), llvm::GlobalValue::LinkageTypes::ExternalLinkage, "b"));
	module->module->getFunctionList ().push_back (function2);
	mu::core::errors::errors errors (*new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::llvm_::module::get_package);
	ctx.push (module);
	ctx.push (new (GC) mu::script::astring::node (std::string (".suffix")));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto package (dynamic_cast <mu::script::package::node *> (ctx.working (0)));
	EXPECT_NE (package, nullptr);
	EXPECT_EQ (package->items.size (), 2);
	EXPECT_NE (package->items.find (U"a"), package->items.end ());
	auto f1 (dynamic_cast <mu::llvm_::function::node *> (package->items.find (U"a")->second));
	EXPECT_NE (f1, nullptr);
	EXPECT_EQ (f1->value (), function1);
	EXPECT_EQ (function1->getNameStr (), std::string ("a.suffix"));
	EXPECT_NE (package->items.find (U"b"), package->items.end ());
	auto f2 (dynamic_cast <mu::llvm_::function::node *> (package->items.find (U"b")->second));
	EXPECT_NE (f2, nullptr);
	EXPECT_EQ (f2->value (), function2);
	EXPECT_EQ (function2->getNameStr (), std::string ("b.suffix"));
}