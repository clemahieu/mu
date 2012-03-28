#include <mu/llvm_test/instruction_package.h>

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
#include <mu/io/debugging/stream.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

void mu::llvm_test::instruction_package::run ()
{
	run_1 ();
	run_2 ();
}

void mu::llvm_test::instruction_package::run_1 ()
{
	mu::script::builder builder (boost::make_shared <mu::io::debugging::stream> (), boost::shared_ptr <mu::script::extensions::node> (mu::script::api::core ())->extensions);
	builder (L"[[~ :~; instruction insert block left right] [instruction left right; value] [insert block value;; inserted] ~ inserted value]"); 
	builder ();
	assert (builder.errors->errors.empty ());
	auto cluster1 (builder.cluster);
	assert (cluster1->routines.size () == 1);
	auto routine1 (cluster1->routines [0]);
	mu::core::errors::errors errors (builder.errors);
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::create_single> ());
	ctx.push (routine1);
	ctx.push (boost::make_shared <mu::llvm_::instructions::add> ());
	ctx.push (boost::make_shared <mu::llvm_::basic_block::insert> ());
	auto block (boost::make_shared <mu::llvm_::basic_block::node> (nullptr));
	ctx.push (block);
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
	mu::script::builder b2 (boost::make_shared <mu::io::debugging::stream> (), boost::shared_ptr <mu::script::extensions::node> (mu::script::api::core ())->extensions);
	b2.analyzer.extensions->extensions_m [std::wstring (L"add")] = boost::make_shared <mu::io::analyzer::extensions::global> (ctx.working (0));
	b2 (L"[[~ :~; number] add [add number number] [add [add number number] number]]");
	b2 ();
	assert (b2.errors->errors.empty ());
	auto cluster2 (b2.cluster);
	assert (cluster2->routines.size () == 1);
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
	ctx.push (boost::make_shared <mu::llvm_::constant::node> (llvm::ConstantInt::get (llvm::Type::getInt32Ty (context), llvm::APInt (32, 1)), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt32Ty (context))));
	auto valid2 (ctx ());
	assert (valid2);
	assert (ctx.working_size () == 1);
	assert (bl->getInstList ().size () == 4);
}

void mu::llvm_test::instruction_package::run_2 ()
{
	mu::script::builder builder (boost::make_shared <mu::io::debugging::stream> (), boost::shared_ptr <mu::script::extensions::node> (mu::script::api::core ())->extensions);
	builder (L"[[~ :~; instruction insert block left right] [instruction left right; value] [insert block value;; inserted] ~ inserted value;; build_insert]"); 
	builder (L"[[~ :~; instruction insert block] .apply build_insert instruction insert block]");
	builder ();
	assert (builder.errors->errors.empty ());
	auto cluster1 (builder.cluster);
	assert (cluster1->routines.size () == 2);
	auto routine1 (cluster1->routines [1]);
	mu::core::errors::errors errors (builder.errors);
	mu::script::context ctx (errors);
	ctx.push (routine1);
	ctx.push (boost::make_shared <mu::llvm_::instructions::add> ());
	ctx.push (boost::make_shared <mu::llvm_::basic_block::insert> ());
	auto block (boost::make_shared <mu::llvm_::basic_block::node> (nullptr));
	ctx.push (block);
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
	mu::script::builder b2 (boost::make_shared <mu::io::debugging::stream> (), boost::shared_ptr <mu::script::extensions::node> (mu::script::api::core ())->extensions);
	b2.analyzer.extensions->extensions_m [std::wstring (L"add")] = boost::make_shared <mu::io::analyzer::extensions::global> (ctx.working (0));
	b2 (L"[[~ :~; number] add [add number number] [add [add number number] number]]");
	b2 ();
	assert (b2.errors->errors.empty ());
	auto cluster2 (b2.cluster);
	assert (cluster2->routines.size () == 1);
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
	ctx.push (boost::make_shared <mu::llvm_::constant::node> (llvm::ConstantInt::get (llvm::Type::getInt32Ty (context), llvm::APInt (32, 1)), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt32Ty (context))));
	auto valid2 (ctx ());
	assert (valid2);
	assert (ctx.working_size () == 1);
	assert (bl->getInstList ().size () == 4);
}