#include "operation.h"

#include <lambda_p_io/source.h>
#include <lambda_p_script_io/builder.h>
#include <lambda_p_llvm/synthesizer/operation.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_script/cluster/node.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_io/ast/cluster.h>
#include <lambda_p_llvm/module/print.h>
#include <lambda_p_llvm/module/verify.h>
#include <lambda_p_io/builder.h>

#include <boost/bind.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

#include <boost/make_shared.hpp>

#include <sstream>

void lambda_p_llvm_test::synthesizer::operation::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
}

void lambda_p_llvm_test::synthesizer::operation::run_1 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> r2;
	a2.push_back (ast);
	a2.push_back (module);
	lambda_p_llvm::synthesizer::operation synthesizer;
	synthesizer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 0);
	lambda_p_llvm::module::print print;
	std::vector <boost::shared_ptr <lambda_p::node>> a3;
	std::vector <boost::shared_ptr <lambda_p::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	lambda_p_llvm::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
}

void lambda_p_llvm_test::synthesizer::operation::run_2 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[fun-t [{] [{ [int-t # d32]]] [add [int-c # d32 # d1] [int-c # d32 # d1]]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> r2;
	a2.push_back (ast);
	a2.push_back (module);
	lambda_p_llvm::synthesizer::operation synthesizer;
	synthesizer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 1);
	lambda_p_llvm::module::print print;
	std::vector <boost::shared_ptr <lambda_p::node>> a3;
	std::vector <boost::shared_ptr <lambda_p::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	lambda_p_llvm::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
}

void lambda_p_llvm_test::synthesizer::operation::run_3 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[fun-t [{ [int-t # d32]] [{ [int-t # d32]]] [:~]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> r2;
	a2.push_back (ast);
	a2.push_back (module);
	lambda_p_llvm::synthesizer::operation synthesizer;
	synthesizer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 1);
	lambda_p_llvm::module::print print;
	std::vector <boost::shared_ptr <lambda_p::node>> a3;
	std::vector <boost::shared_ptr <lambda_p::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	lambda_p_llvm::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
}

void lambda_p_llvm_test::synthesizer::operation::run_4 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [add [:~]]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> r2;
	a2.push_back (ast);
	a2.push_back (module);
	lambda_p_llvm::synthesizer::operation synthesizer;
	synthesizer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 1);
	lambda_p_llvm::module::print print;
	std::vector <boost::shared_ptr <lambda_p::node>> a3;
	std::vector <boost::shared_ptr <lambda_p::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	lambda_p_llvm::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
}

void lambda_p_llvm_test::synthesizer::operation::run_5 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[fun-t [{ ] [{ ]] [:~]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> r2;
	a2.push_back (ast);
	a2.push_back (module);
	lambda_p_llvm::synthesizer::operation synthesizer;
	synthesizer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 1);
	lambda_p_llvm::module::print print;
	std::vector <boost::shared_ptr <lambda_p::node>> a3;
	std::vector <boost::shared_ptr <lambda_p::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	lambda_p_llvm::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
}

void lambda_p_llvm_test::synthesizer::operation::run_6 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[fun-t [{ [int-t # d32] [int-t # d16]] [{ [int-t # d32] [int-t # d16]]] [:~]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> r2;
	a2.push_back (ast);
	a2.push_back (module);
	lambda_p_llvm::synthesizer::operation synthesizer;
	synthesizer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 1);
	lambda_p_llvm::module::print print;
	std::vector <boost::shared_ptr <lambda_p::node>> a3;
	std::vector <boost::shared_ptr <lambda_p::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	lambda_p_llvm::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
}

void lambda_p_llvm_test::synthesizer::operation::run_7 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	std::wstringstream code;
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [add [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [and [:~]]";
	code << L"[fun-t [{ [int-t # d32]] [{ [int-t # d32]]] [bitcast [:~] [int-t # d32]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [ashr [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d1]]] [icmp eq [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d1]]] [icmp ne [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d1]]] [icmp sge [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d1]]] [icmp sgt [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d1]]] [icmp sle [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d1]]] [icmp slt [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d1]]] [icmp uge [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d1]]] [icmp ugt [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d1]]] [icmp ule [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d1]]] [icmp ult [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [lshr [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [mul [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [or [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [sdiv [:~]]";
	code << L"[fun-t [{ [int-t # d32]] [{ [int-t # d64]]] [sext [:~] [int-t # d64]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [shl [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [srem [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [sub [:~]]";
	code << L"[fun-t [{ [int-t # d32]] [{ [int-t # d16]]] [trunc [:~] [int-t # d16]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [udiv [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [urem [:~]]";
	code << L"[fun-t [{ [int-t # d32] [int-t # d32]] [{ [int-t # d32]]] [xor [:~]]";
	code << L"[fun-t [{ [int-t # d32]] [{ [int-t # d64]]] [zext [:~] [int-t # d64]]";
	source (code.str ());
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> r2;
	a2.push_back (ast);
	a2.push_back (module);
	lambda_p_llvm::synthesizer::operation synthesizer;
	synthesizer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 27);
	lambda_p_llvm::module::print print;
	std::vector <boost::shared_ptr <lambda_p::node>> a3;
	std::vector <boost::shared_ptr <lambda_p::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	lambda_p_llvm::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
}