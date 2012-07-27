#include <mu/script/builder.h>
#include <mu/io/source.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/closure/create_single.h>
#include <mu/llvm_/instructions/add.h>
#include <mu/llvm_/basic_block/insert.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/llvm_/constant_int/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/script/context.h>
#include <mu/script/api.h>
#include <mu/script/extensions/node.h>
#include <mu/core/routine.h>
#include <mu/script/cluster/node.h>
#include <mu/script/runtime/routine.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (llvm_test, instruction_package1)
{
	mu::script::builder builder (mu::script::api::core ()->extensions);
	mu::io::process (builder, U"[[~ :~; instruction insert block left right] [instruction left right; value] [insert block value;; inserted] ~ inserted value]"); 
	EXPECT_TRUE (builder.errors.errors.empty ());
	auto cluster1 (builder.cluster);
	EXPECT_EQ (cluster1->routines.size (), 1);
	auto routine1 (cluster1->routines [0]);
	mu::script::context ctx (builder.errors);
	ctx.push (new (GC) mu::script::closure::create_single);
	ctx.push (routine1);
	ctx.push (new (GC) mu::llvm_::instructions::add);
	ctx.push (new (GC) mu::llvm_::basic_block::insert);
	auto block (new (GC) mu::llvm_::basic_block::node (nullptr));
	ctx.push (block);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	mu::script::builder b2 (mu::script::api::core ()->extensions);
	(*b2.analyzer.extensions) (mu::string (U"add"), new (GC) mu::io::analyzer::extensions::global (ctx.working (0)));
    mu::io::process (b2, U"[[~ :~; number] add [add number number] [add [add number number] number]]");
	EXPECT_TRUE (b2.errors.errors.empty ());
	auto cluster2 (b2.cluster);
	EXPECT_EQ (cluster2->routines.size (), 1);
	auto routine2 (cluster2->routines [0]);
	llvm::LLVMContext context;
	auto module (new llvm::Module (llvm::StringRef (), context));
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::LinkageTypes::ExternalLinkage));
	module->getFunctionList ().push_back (function);
	auto bl (llvm::BasicBlock::Create (context));
	block->block = bl;
	function->getBasicBlockList ().push_back (bl);
	ctx.drop ();
	ctx.push (routine2);
	ctx.push (new (GC) mu::llvm_::constant::node (llvm::ConstantInt::get (llvm::Type::getInt32Ty (context), llvm::APInt (32, 1)), new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt32Ty (context))));
	auto valid2 (ctx ());
	EXPECT_EQ (valid2, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (bl->getInstList ().size (), 4);
}

TEST (llvm_test, instruction_package2)
{
	mu::script::builder builder (mu::script::api::core ()->extensions);
    mu::stringstream stream;
    stream << U"[[~ :~; instruction insert block left right] [instruction left right; value] [insert block value;; inserted] ~ inserted value;; build_insert]"; 
	stream << U"[[~ :~; instruction insert block] .apply build_insert instruction insert block]";
    mu::io::process (builder, stream);
	ASSERT_TRUE (builder.errors.errors.empty ());
	auto cluster1 (builder.cluster);
	ASSERT_TRUE (cluster1->routines.size () == 2);
	auto routine1 (cluster1->routines [1]);
	mu::script::context ctx (builder.errors);
	ctx.push (routine1);
	ctx.push (new (GC) mu::llvm_::instructions::add);
	ctx.push (new (GC) mu::llvm_::basic_block::insert);
	auto block (new (GC) mu::llvm_::basic_block::node (nullptr));
	ctx.push (block);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	mu::script::builder b2 (mu::script::api::core ()->extensions);
	(*b2.analyzer.extensions) (mu::string (U"add"), new (GC) mu::io::analyzer::extensions::global (ctx.working (0)));
	mu::io::process (b2, U"[[~ :~; number] add [add number number] [add [add number number] number]]");
	EXPECT_TRUE (b2.errors.errors.empty ());
	auto cluster2 (b2.cluster);
	EXPECT_EQ (cluster2->routines.size (), 1);
	auto routine2 (cluster2->routines [0]);
	llvm::LLVMContext context;
	auto module (new llvm::Module (llvm::StringRef (), context));
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::LinkageTypes::ExternalLinkage));
	module->getFunctionList ().push_back (function);
	auto bl (llvm::BasicBlock::Create (context));
	block->block = bl;
	function->getBasicBlockList ().push_back (bl);
	ctx.drop ();
	ctx.push (routine2);
	ctx.push (new (GC) mu::llvm_::constant::node (llvm::ConstantInt::get (llvm::Type::getInt32Ty (context), llvm::APInt (32, 1)), new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt32Ty (context))));
	auto valid2 (ctx ());
	EXPECT_EQ (valid2, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (bl->getInstList ().size (), 4);
}