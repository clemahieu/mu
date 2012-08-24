#include <mu/core/expression.h>
#include <mu/core/routine.h>
#include <mu/io/ast/expression.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

TEST (llvm_test, DISABLED_extension1)
{
    assert (false);
	//mu::script_io::builder builder;
	//mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	//source (L"[.llvm [[# d32 add and ashr cmpxchg load lshr mul or sdiv shl srem store sub trunc udiv urem xor]]]");
	//source ();
	//assert (builder.errors->errors.empty ());
	//assert (builder.clusters.size () == 1);
	//auto cluster (builder.clusters [0]);
	//assert (cluster->routines.size () == 1);
}