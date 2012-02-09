#include "instruction_package.h"

#include <lambda_p_script_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p_script/cluster/node.h>
#include <lambda_p_script/closure/create_single.h>
#include <lambda_p_llvm/instructions/add.h>
#include <lambda_p_llvm/basic_block/insert.h>
#include <lambda_p_llvm/basic_block/node.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_io/analyzer/extensions/extensions.h>
#include <lambda_p_io/analyzer/extensions/global.h>
#include <lambda_p_llvm/constant_int/node.h>
#include <lambda_p_llvm/integer_type/node.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

void lambda_p_llvm_test::instruction_package::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_llvm_test::instruction_package::run_1 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~; instruction insert block left right] [instruction left right; value] [insert block value;; inserted] ~ inserted value]"); 
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster1 (builder.clusters [0]);
	assert (cluster1->routines.size () == 1);
	auto routine1 (cluster1->routines [0]);
	lambda_p_script::closure::create_single create;
	std::vector <boost::shared_ptr <lambda_p::node>> a1;
	std::vector <boost::shared_ptr <lambda_p::node>> r1;
	a1.push_back (routine1);
	a1.push_back (boost::make_shared <lambda_p_llvm::instructions::add> ());
	a1.push_back (boost::make_shared <lambda_p_llvm::basic_block::insert> ());
	auto block (boost::make_shared <lambda_p_llvm::basic_block::node> (nullptr));
	a1.push_back (block);
	create.perform (builder.errors, a1, r1);
	assert (r1.size () == 1);
	lambda_p_script_io::builder b2;
	lambda_p_io::source s2 (boost::bind (&lambda_p_io::lexer::lexer::operator(), &b2.lexer, _1));
	b2.analyzer.extensions->extensions_m [std::wstring (L"add")] = boost::make_shared <lambda_p_io::analyzer::extensions::global> (r1 [0]);
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
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> r2;
	a2.push_back (boost::make_shared <lambda_p_llvm::constant::node> (llvm::ConstantInt::get (llvm::Type::getInt32Ty (context), llvm::APInt (32, 1)), boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt32Ty (context))));
	routine2->perform (b2.errors, a2, r2);
	assert (b2.errors->errors.empty ());
	assert (r2.size () == 1);
	assert (bl->getInstList ().size () == 4);
}

void lambda_p_llvm_test::instruction_package::run_2 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~; instruction insert block left right] [instruction left right; value] [insert block value;; inserted] ~ inserted value;; build_insert]"); 
	source (L"[[:~; instruction insert block] .apply build_insert instruction insert block]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster1 (builder.clusters [0]);
	assert (cluster1->routines.size () == 2);
	auto routine1 (cluster1->routines [1]);
	std::vector <boost::shared_ptr <lambda_p::node>> a1;
	std::vector <boost::shared_ptr <lambda_p::node>> r1;
	a1.push_back (boost::make_shared <lambda_p_llvm::instructions::add> ());
	a1.push_back (boost::make_shared <lambda_p_llvm::basic_block::insert> ());
	auto block (boost::make_shared <lambda_p_llvm::basic_block::node> (nullptr));
	a1.push_back (block);
	routine1->perform (builder.errors, a1, r1);
	assert (r1.size () == 1);
	lambda_p_script_io::builder b2;
	lambda_p_io::source s2 (boost::bind (&lambda_p_io::lexer::lexer::operator(), &b2.lexer, _1));
	b2.analyzer.extensions->extensions_m [std::wstring (L"add")] = boost::make_shared <lambda_p_io::analyzer::extensions::global> (r1 [0]);
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
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> r2;
	a2.push_back (boost::make_shared <lambda_p_llvm::constant::node> (llvm::ConstantInt::get (llvm::Type::getInt32Ty (context), llvm::APInt (32, 1)), boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt32Ty (context))));
	routine2->perform (b2.errors, a2, r2);
	assert (b2.errors->errors.empty ());
	assert (r2.size () == 1);
	assert (bl->getInstList ().size () == 4);
}