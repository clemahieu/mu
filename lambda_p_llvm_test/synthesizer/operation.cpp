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
#include <lambda_p_llvm/cluster/node.h>
#include <lambda_p_llvm/function/node.h>
#include <lambda_p_llvm/type/node.h>

#include <boost/bind.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>

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
	run_8 ();
	run_9 ();
	run_10 ();
	run_11 ();
	run_12 ();
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
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 0);
	assert (cluster->names.size () == 0);
}

void lambda_p_llvm_test::synthesizer::operation::run_2 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~] [~ [i32]] [add #i 32 d1 #i 32 d1]");
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
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
	auto routine (cluster->routines [0]);
	assert (routine->value()->getType ()->isPointerTy ());
	auto ptr (llvm::dyn_cast <llvm::PointerType> (routine->value ()->getType ()));
	assert (ptr != nullptr);
	assert (ptr->getElementType ()->isFunctionTy ());
}

void lambda_p_llvm_test::synthesizer::operation::run_3 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ [i32]] [~ [i32]] [:~]");
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
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
}

void lambda_p_llvm_test::synthesizer::operation::run_4 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ [i32] [i32]] [~ [i32]] [add [:~]]");
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
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
}

void lambda_p_llvm_test::synthesizer::operation::run_5 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ ] [~ ] [:~]");
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
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
}

void lambda_p_llvm_test::synthesizer::operation::run_6 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ [i32] [i16]] [~ [i32] [i16]] [:~]");
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
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
}

void lambda_p_llvm_test::synthesizer::operation::run_7 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ [i32] [ptr [i32]]] [~] [store [:~]]");
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
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
}

void lambda_p_llvm_test::synthesizer::operation::run_8 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ [i32] [ptr [i32]]] [~] [~ [store [:~]] [store [:~]]]");
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
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
}

void lambda_p_llvm_test::synthesizer::operation::run_9 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	std::wstringstream code;
	code << L"[~ [i32] [i32]] [~ [i32]] [add [:~]]";
	code << L"[~ [i32] [i32]] [~ [i32]] [and [:~]]";
	code << L"[~ [i32]] [~ [i32]] [bitcast [:~] [i32]]";
	code << L"[~ [i32] [i32]] [~ [i32]] [ashr [:~]]";
	code << L"[~ [i32] [i32]] [~ [i1]] [icmp eq [:~]]";
	code << L"[~ [i32] [i32]] [~ [i1]] [icmp ne [:~]]";
	code << L"[~ [i32] [i32]] [~ [i1]] [icmp sge [:~]]";
	code << L"[~ [i32] [i32]] [~ [i1]] [icmp sgt [:~]]";
	code << L"[~ [i32] [i32]] [~ [i1]] [icmp sle [:~]]";
	code << L"[~ [i32] [i32]] [~ [i1]] [icmp slt [:~]]";
	code << L"[~ [i32] [i32]] [~ [i1]] [icmp uge [:~]]";
	code << L"[~ [i32] [i32]] [~ [i1]] [icmp ugt [:~]]";
	code << L"[~ [i32] [i32]] [~ [i1]] [icmp ule [:~]]";
	code << L"[~ [i32] [i32]] [~ [i1]] [icmp ult [:~]]";
	code << L"[~ [i64]] [~ [ptr [i8]]] [inttoptr [:~] [ptr [i8]]]";
	code << L"[~ [ptr [i32]]] [~ [i32]] [load [:~]]";
	code << L"[~ [i32] [i32]] [~ [i32]] [lshr [:~]]";
	code << L"[~ [i32] [i32]] [~ [i32]] [mul [:~]]";
	code << L"[~ [i32] [i32]] [~ [i32]] [or [:~]]";
	code << L"[~ [ptr [i8]]] [~ [i64]] [ptrtoint [:~] [i64]]";
	code << L"[~ [i32] [i32]] [~ [i32]] [sdiv [:~]]";
	code << L"[~ [i32]] [~ [i64]] [sext [:~] [i64]]";
	code << L"[~ [i32] [i32]] [~ [i32]] [shl [:~]]";
	code << L"[~ [i32] [i32]] [~ [i32]] [srem [:~]]";
	code << L"[~ [i32] [ptr [i32]]] [~] [store [:~]]";
	code << L"[~ [i32] [i32]] [~ [i32]] [sub [:~]]";
	code << L"[~ [i32]] [~ [i16]] [trunc [:~] [i16]]";
	code << L"[~ [i32] [i32]] [~ [i32]] [udiv [:~]]";
	code << L"[~ [i32] [i32]] [~ [i32]] [urem [:~]]";
	code << L"[~ [i32] [i32]] [~ [i32]] [xor [:~]]";
	code << L"[~ [i32]] [~ [i64]] [zext [:~] [i64]]";
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
	assert (module->module->getFunctionList ().size () == 31);
	lambda_p_llvm::module::print print;
	std::vector <boost::shared_ptr <lambda_p::node>> a3;
	std::vector <boost::shared_ptr <lambda_p::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	lambda_p_llvm::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 31);
	assert (cluster->names.size () == 0);
}

void lambda_p_llvm_test::synthesizer::operation::run_10 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	std::wstringstream code;
	code << L"[~ ] [~ [ptr [fun-t [{ ] [{ ]]]] [~ 2 ;; 1]";
	code << L"[~ ] [~ ] [~ ;; 2]";
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
	assert (module->module->getFunctionList ().size () == 2);
	lambda_p_llvm::module::print print;
	std::vector <boost::shared_ptr <lambda_p::node>> a3;
	std::vector <boost::shared_ptr <lambda_p::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	lambda_p_llvm::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 2);
	assert (cluster->names.size () == 2);
	auto rout1 (cluster->routines [0]);
	auto rout2 (cluster->routines [1]);
	auto n1 (cluster->names.find (std::wstring (L"1")));
	auto n2 (cluster->names.find (std::wstring (L"2")));
	assert (n1 != cluster->names.end ());
	assert (n2 != cluster->names.end ());
	assert (n1->second == rout1);
	assert (n2->second == rout2);
}

void lambda_p_llvm_test::synthesizer::operation::run_11 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	std::wstringstream code;
	code << L"[~ ] [~ [i32]] [call 2 ;; 1]";
	code << L"[~ ] [~ [i32]] [~ #i 32 d42 ;; 2]";
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
	assert (module->module->getFunctionList ().size () == 2);
	lambda_p_llvm::module::print print;
	std::vector <boost::shared_ptr <lambda_p::node>> a3;
	std::vector <boost::shared_ptr <lambda_p::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	lambda_p_llvm::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 2);
	assert (cluster->names.size () == 2);
	auto rout1 (cluster->routines [0]);
	auto rout2 (cluster->routines [1]);
	auto n1 (cluster->names.find (std::wstring (L"1")));
	auto n2 (cluster->names.find (std::wstring (L"2")));
	assert (n1 != cluster->names.end ());
	assert (n2 != cluster->names.end ());
	assert (n1->second == rout1);
	assert (n2->second == rout2);
}

void lambda_p_llvm_test::synthesizer::operation::run_12 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	std::wstringstream code;
	code << L"[~ ] [~ [ptr [i16]]] [~ ` test_string]";
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
}