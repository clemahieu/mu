#include "analyzer.h"

#include <lambda_p/expression.h>
#include <lambda_p/routine.h>
#include <lambda_p_io/builder.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/cluster.h>
#include <lambda_p_llvm/analyzer/operation.h>

#include <boost/bind.hpp>

void lambda_p_llvm_test::analyzer::run ()
{
	run_1 ();
}

void lambda_p_llvm_test::analyzer::run_1 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[.ast [[# d32 add and ashr bitcast cmpxchg icmp integer inttoptr load lshr mul or pointer ptrtoint sdiv sext shl srem store structure sub trunc udiv urem void xor zext]]]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
	assert (routine->body->dependencies.size () == 1);
	auto cl (boost::dynamic_pointer_cast <lambda_p_io::ast::cluster> (routine->body->dependencies [0]));
	assert (cl != nullptr);
	assert (cl->expressions.size () == 1);
	lambda_p_llvm::analyzer::operation analyzer;
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	arguments.push_back (cl);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	analyzer (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 1);
	auto clust (boost::dynamic_pointer_cast <lambda_p::cluster> (results [0]));
	assert (clust != nullptr);
	assert (clust->routines.size () == 1);
	auto routine1 (boost::dynamic_pointer_cast <lambda_p::routine> (clust->routines [0]));
	assert (routine1.get () != nullptr);
	auto dependencies (routine1->body->dependencies);
	assert (dependencies.size () == 28);
}