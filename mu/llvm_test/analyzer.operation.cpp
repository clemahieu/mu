#include <mu/llvm_test/analyzer.operation.h>

#include <mu/io/source.h>
#include <mu/script_io/builder.h>
#include <mu/llvm_/analyzer.operation.h>
#include <mu/llvm_/module.node.h>
#include <mu/script/cluster/node.h>
#include <mu/script/runtime/routine.h>
#include <mu/io/ast.cluster.h>
#include <mu/llvm_/module.print.h>
#include <mu/llvm_/module.verify.h>
#include <mu/io/builder.h>
#include <mu/llvm_/cluster.node.h>
#include <mu/llvm_/function.node.h>
#include <mu/llvm_/type.node.h>
#include <mu/llvm_/context.node.h>

#include <boost/bind.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>

#include <boost/make_shared.hpp>

#include <sstream>

void mu::llvm_test::analyzer::operation::run ()
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
	run_13 ();
	run_14 ();
}

void mu::llvm_test::analyzer::operation::run_1 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 0);
	mu::llvm_::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	mu::llvm_::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 0);
	assert (cluster->names.size () == 0);
}

void mu::llvm_test::analyzer::operation::run_2 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~] [~ [i32]] [add #i 32 d1 #i 32 d1]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 1);
	mu::llvm_::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	mu::llvm_::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
	auto routine (cluster->routines [0]);
	assert (routine->value()->getType ()->isPointerTy ());
	auto ptr (llvm::dyn_cast <llvm::PointerType> (routine->value ()->getType ()));
	assert (ptr != nullptr);
	assert (ptr->getElementType ()->isFunctionTy ());
}

void mu::llvm_test::analyzer::operation::run_3 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ [i32]] [~ [i32]] [:~]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 1);
	mu::llvm_::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	mu::llvm_::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
}

void mu::llvm_test::analyzer::operation::run_4 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ [i32] [i32]] [~ [i32]] [add [:~]]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 1);
	mu::llvm_::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	mu::llvm_::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
}

void mu::llvm_test::analyzer::operation::run_5 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ ] [~ ] [:~]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 1);
	mu::llvm_::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	mu::llvm_::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
}

void mu::llvm_test::analyzer::operation::run_6 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ [i32] [i16]] [~ [i32] [i16]] [:~]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 1);
	mu::llvm_::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	mu::llvm_::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
}

void mu::llvm_test::analyzer::operation::run_7 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ [i32] [ptr [i32]]] [~] [store [:~]]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 1);
	mu::llvm_::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	mu::llvm_::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
}

void mu::llvm_test::analyzer::operation::run_8 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[~ [i32] [ptr [i32]]] [~] [~ [store [:~]] [store [:~]]]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 1);
	mu::llvm_::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	mu::llvm_::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 1);
	assert (cluster->names.size () == 0);
}

void mu::llvm_test::analyzer::operation::run_9 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
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
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 31);
	mu::llvm_::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	mu::llvm_::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 31);
	assert (cluster->names.size () == 0);
}

void mu::llvm_test::analyzer::operation::run_10 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	std::wstringstream code;
	code << L"[~ ] [~ [ptr [fun-t [{ ] [{ ]]]] [~ 2 ;; 1]";
	code << L"[~ ] [~ ] [~ ;; 2]";
	source (code.str ());
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 2);
	mu::llvm_::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	mu::llvm_::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (r2 [0]));
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

void mu::llvm_test::analyzer::operation::run_11 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	std::wstringstream code;
	code << L"[~ ] [~ [i32]] [call 2 ;; 1]";
	code << L"[~ ] [~ [i32]] [~ #i 32 d42 ;; 2]";
	source (code.str ());
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 2);
	mu::llvm_::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	mu::llvm_::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (r2 [0]));
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

void mu::llvm_test::analyzer::operation::run_12 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	std::wstringstream code;
	code << L"[~ ] [~ [ptr [i16]]] [~ ` test_string]";
	source (code.str ());
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
}

void mu::llvm_test::analyzer::operation::run_13 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	std::wstringstream code;
	code << L"[~ ] [~ ] [call 2 [call 2];; 1]";
	code << L"[~ ] [~ ] [~ ;; 2]";
	source (code.str ());
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 2);
	mu::llvm_::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	mu::llvm_::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (r2 [0]));
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

void mu::llvm_test::analyzer::operation::run_14 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	std::wstringstream code;
	code << L"[~ ] [~ ] [call 3 [call 2];; 1]";
	code << L"[~ ] [~ [i16] [i16]] [~ #i 16 d0 #i 16 d0;; 2]";
	code << L"[~ [i16] [i16]] [~ ] [~ ;; 3]";
	source (code.str ());
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	assert (builder.clusters.size () == 1);
	auto ast (builder.clusters [0]);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	a2.push_back (boost::make_shared <mu::llvm_::context::node> (&context_l));
	a2.push_back (module);
	a2.push_back (ast);
	mu::llvm_::analyzer::operation analyzer;
	analyzer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 3);
	mu::llvm_::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (module);
	print (builder.errors, a3, r3);
	mu::llvm_::module::verify verify;
	verify (builder.errors, a3, r3);
	assert (builder.errors->errors.empty ());
	assert (r2.size () == 1);
	auto cluster (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (r2 [0]));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 3);
	assert (cluster->names.size () == 3);
	auto rout1 (cluster->routines [0]);
	auto rout2 (cluster->routines [1]);
	auto rout3 (cluster->routines [2]);
	auto n1 (cluster->names.find (std::wstring (L"1")));
	auto n2 (cluster->names.find (std::wstring (L"2")));
	auto n3 (cluster->names.find (std::wstring (L"3")));
	assert (n1 != cluster->names.end ());
	assert (n2 != cluster->names.end ());
	assert (n3 != cluster->names.end ());
	assert (n1->second == rout1);
	assert (n2->second == rout2);
	assert (n3->second == rout3);
}
