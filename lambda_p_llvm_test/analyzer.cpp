#include "analyzer.h"

#include <mu/core/expression.h>
#include <mu/core/routine.h>
#include <mu/io/builder.h>
#include <mu/io/ast/expression.h>
#include <mu/io/ast/cluster.h>
#include <lambda_p_llvm/analyzer/operation.h>

#include <boost/bind.hpp>

void lambda_p_llvm_test::analyzer::run ()
{
	run_1 ();
}

void lambda_p_llvm_test::analyzer::run_1 ()
{
	//mu::io::builder builder;
	//mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	//source (L"[.ast [[# d32 add and ashr bitcast cmpxchg icmp integer inttoptr load lshr mul or pointer ptrtoint sdiv sext shl srem store structure sub trunc udiv urem void xor zext]]]");
	//source ();
	//assert (builder.errors->errors.empty ());
	//assert (builder.clusters.size () == 1);
	//auto cluster (builder.clusters [0]);
	//assert (cluster->routines.size () == 1);
	//auto routine (cluster->routines [0]);
	//assert (routine->body->dependencies.size () == 1);
	//auto cl (boost::dynamic_pointer_cast <mu::io::ast::cluster> (routine->body->dependencies [0]));
	//assert (cl != nullptr);
	//assert (cl->expressions.size () == 1);
	//lambda_p_llvm::analyzer::operation analyzer;
	//std::vector <boost::shared_ptr <mu::core::node>> arguments;
	//arguments.push_back (cl);
	//std::vector <boost::shared_ptr <mu::core::node>> results;
	//analyzer (builder.errors, arguments, results);
	//assert (builder.errors->errors.empty ());
	//assert (results.size () == 1);
	//auto clust (boost::dynamic_pointer_cast <mu::core::cluster> (results [0]));
	//assert (clust != nullptr);
	//assert (clust->routines.size () == 1);
	//auto routine1 (boost::dynamic_pointer_cast <mu::core::routine> (clust->routines [0]));
	//assert (routine1.get () != nullptr);
	//auto dependencies (routine1->body->dependencies);
	//assert (dependencies.size () == 28);
}