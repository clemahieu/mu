#include <mu/script/context.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/debugging_trace_types.h>
#include <mu/script/values_operation.h>
#include <mu/script/builder.h>
#include <mu/io/source.h>
#include <mu/script/cluster_node.h>
#include <mu/script/runtime_routine.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

TEST (script_test, trace_types1)
{
	//mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	//mu::script::context context (errors);
	//auto stream (boost::make_shared <mu::io::debugging::stream> ());
	//context.push (boost::make_shared <mu::script::debugging::trace_types> ());
	//auto valid (context ());
	//assert (valid);
	//assert (context.working_size () == 1);
	//auto operation (boost::dynamic_pointer_cast <mu::script::values::operation> (context.working (0)));
	//assert (operation != nullptr);
	//assert (operation->values.size () == 1);
}

TEST (script_test, trace_types2)
{
	//mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	//mu::script::context context (errors);
	//mu::script::builder builder;
	//builder.analyzer.extensions->extensions_m [U"trace"] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::debugging::trace_types> ());
	//builder (U"[trace :~]");
	//builder ();
	//assert (builder.errors->errors.empty ());
	//auto cluster (builder.cluster);
	//assert (cluster->routines.size () == 1);
	//auto routine (cluster->routines [0]);
	//context.push (routine);
	//auto valid (context ());
	//assert (valid);
	//assert (context.working_size () == 1);
	//auto trace (boost::dynamic_pointer_cast <mu::script::values::operation> (context.working (0)));
	//assert (trace != nullptr);
	//assert (trace->values.size () == 3);
}