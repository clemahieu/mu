#include <mu/script/builder.h>
#include <mu/io/source.h>
#include <mu/script/context.h>
#include <mu/script/cluster/node.h>
#include <mu/script/debugging/trace_target.h>
#include <mu/script/runtime/routine.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/fail/operation.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/analyzer/extensions/global.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

TEST (script_test, builder1)
{
	//mu::script::builder builder;
	//builder.analyzer.extensions->extensions_m [L"fail"] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::fail::operation> ());
	//builder (L"[fail]");
	//builder ();
	//auto cluster (builder.cluster);
	//assert (cluster->routines.size () == 1);
	//auto routine (cluster->routines [0]);
	//mu::script::context context;
	//mu::core::errors::errors errors (boost::make_shared <mu::script::debugging::trace_target> (builder.errors, context, builder.cluster_info));
	//context.errors = errors;
	//context.push (routine);
	//auto valid (context ());
	//assert (!valid);
	//assert (builder.errors->errors.size () == 1);
}

TEST (script_test, builder2)
{
	//mu::script::builder builder;
	//builder.analyzer.extensions->extensions_m [L"fail"] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::fail::operation> ());
	//builder (L"[  [1]] [ \n  [2];;1] [  \n\n [3];;2] [ \n  [4];;3] [\nfail;;4]");
	//builder ();
	//auto cluster (builder.cluster);
	//assert (cluster->routines.size () == 5);
	//auto routine (cluster->routines [0]);
	//mu::script::context context;
	//mu::core::errors::errors errors (boost::make_shared <mu::script::debugging::trace_target> (builder.errors, context, builder.cluster_info));
	//context.errors = errors;
	//context.push (routine);
	//auto valid (context ());
	//assert (!valid);
	//assert (builder.errors->errors.size () == 1);
}