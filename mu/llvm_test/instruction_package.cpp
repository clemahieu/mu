#include "instruction_package.h"

#include <mu/script_io/builder.h>
#include <mu/io/source.h>
#include <mu/script/cluster/node.h>
#include <mu/script/closure/create_single.h>
#include <mu/llvm_/instructions/add.h>
#include <mu/llvm_/basic_block/insert.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/script/runtime/routine.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/llvm_/constant_int/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/script/context.h>

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
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~; instruction insert block left right] [instruction left right; value] [insert block value;; inserted] ~ inserted value]"); 
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster1 (builder.clusters [0]);
	assert (cluster1->routines.size () == 1);
	auto routine1 (cluster1->routines [0]);
	mu::script::closure::create_single create;
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	a1.push_back (routine1);
	a1.push_back (boost::make_shared <mu::llvm_::instructions::add> ());
	a1.push_back (boost::make_shared <mu::llvm_::basic_block::insert> ());
	auto block (boost::make_shared <mu::llvm_::basic_block::node> (nullptr));
	a1.push_back (block);
	std::vector <std::type_info const *> stack;
    auto ctx (mu::script::context (builder.errors, a1, r1, stack));
	create (ctx);
	assert (r1.size () == 1);
	mu::script_io::builder b2;
	mu::io::source s2 (boost::bind (&mu::io::lexer::lexer::operator(), &b2.lexer, _1));
	b2.analyzer.extensions->extensions_m [std::wstring (L"add")] = boost::make_shared <mu::io::analyzer::extensions::global> (r1 [0]);
	s2 (L"[[:~; number] add [add number number] [add [add number number] number]]");
	s2 ();
	assert (b2.errors->errors.empty ());
	assert (b2.clusters.size () == 1);
	auto cluster2 (b2.clusters [0]);
	assert (cluster2->routines.size () == 1);
	auto routine2 (cluster2->routines [0]);
	llvm::LLVMContext context;
	auto module (new llvm::Module (llvm::StringRef (), context));
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::LinkageTypes::ExternalLinkage));
	module->getFunctionList ().push_back (function);
	auto bl (llvm::BasicBlock::Create (context));
	block->block = bl;
	function->getBasicBlockList ().push_back (bl);
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::constant::node> (llvm::ConstantInt::get (llvm::Type::getInt32Ty (context), llvm::APInt (32, 1)), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt32Ty (context))));
	std::vector <std::type_info const *> stack2;
	auto ctx2 (mu::script::context (b2.errors, a2, r2, stack2));
    (*routine2) (ctx2);
	assert (b2.errors->errors.empty ());
	assert (r2.size () == 1);
	assert (bl->getInstList ().size () == 4);
}

void mu::llvm_test::instruction_package::run_2 ()
{
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~; instruction insert block left right] [instruction left right; value] [insert block value;; inserted] ~ inserted value;; build_insert]"); 
	source (L"[[:~; instruction insert block] .apply build_insert instruction insert block]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster1 (builder.clusters [0]);
	assert (cluster1->routines.size () == 2);
	auto routine1 (cluster1->routines [1]);
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	a1.push_back (boost::make_shared <mu::llvm_::instructions::add> ());
	a1.push_back (boost::make_shared <mu::llvm_::basic_block::insert> ());
	auto block (boost::make_shared <mu::llvm_::basic_block::node> (nullptr));
	a1.push_back (block);
	std::vector <std::type_info const *> stack;
    auto ctx (mu::script::context (builder.errors, a1, r1, stack));
	(*routine1) (ctx);
	assert (r1.size () == 1);
	mu::script_io::builder b2;
	mu::io::source s2 (boost::bind (&mu::io::lexer::lexer::operator(), &b2.lexer, _1));
	b2.analyzer.extensions->extensions_m [std::wstring (L"add")] = boost::make_shared <mu::io::analyzer::extensions::global> (r1 [0]);
	s2 (L"[[:~; number] add [add number number] [add [add number number] number]]");
	s2 ();
	assert (b2.errors->errors.empty ());
	assert (b2.clusters.size () == 1);
	auto cluster2 (b2.clusters [0]);
	assert (cluster2->routines.size () == 1);
	auto routine2 (cluster2->routines [0]);
	llvm::LLVMContext context;
	auto module (new llvm::Module (llvm::StringRef (), context));
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::LinkageTypes::ExternalLinkage));
	module->getFunctionList ().push_back (function);
	auto bl (llvm::BasicBlock::Create (context));
	block->block = bl;
	function->getBasicBlockList ().push_back (bl);
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::constant::node> (llvm::ConstantInt::get (llvm::Type::getInt32Ty (context), llvm::APInt (32, 1)), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt32Ty (context))));
	std::vector <std::type_info const *> stack2;
    auto ctx2 (mu::script::context (b2.errors, a2, r2, stack2));
	(*routine2) (ctx2);
	assert (b2.errors->errors.empty ());
	assert (r2.size () == 1);
	assert (bl->getInstList ().size () == 4);
}