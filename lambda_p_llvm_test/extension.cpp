#include "extension.h"

#include <mu/core/expression.h>
#include <mu/core/routine.h>
#include <mu/io/builder.h>
#include <mu/io/ast/expression.h>
#include <lambda_p_script_io/builder.h>
#include <lambda_p_script/cluster/node.h>

#include <boost/bind.hpp>

void lambda_p_llvm_test::extension::run ()
{
	run_1 ();
}

void lambda_p_llvm_test::extension::run_1 ()
{
	//lambda_p_script_io::builder builder;
	//mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	//source (L"[.llvm [[# d32 add and ashr cmpxchg load lshr mul or sdiv shl srem store sub trunc udiv urem xor]]]");
	//source ();
	//assert (builder.errors->errors.empty ());
	//assert (builder.clusters.size () == 1);
	//auto cluster (builder.clusters [0]);
	//assert (cluster->routines.size () == 1);
}