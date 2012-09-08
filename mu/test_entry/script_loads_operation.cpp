#include <mu/core/errors/error_list.h>
#include <mu/script/loads_operation.h>
#include <mu/script/cluster_node.h>
#include <mu/script/string_node.h>
#include <mu/script/context.h>
#include <mu/io/analyzer_extensions.h>
#include <mu/script/file_node.h>
#include <mu/script/file_open.h>

#include <boost/filesystem.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, loads1)
{
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
    auto path (boost::filesystem3::current_path ());
    path /= "source_test.mu";
    auto file (mu::script::file::open::core (path));
    ASSERT_TRUE (file != nullptr);
	ctx.push (new (GC) mu::script::loads::operation);
	ctx.push (file);
	auto valid (ctx ());
    ASSERT_TRUE (valid);
	ASSERT_TRUE (ctx.working_size () == 1);
	auto cluster (dynamic_cast <mu::script::cluster::node *> (ctx.working (0)));
	ASSERT_TRUE (cluster != nullptr);
	auto a (cluster->routines.find (mu::string (U"a")));
    ASSERT_TRUE (a != cluster->routines.end ());
	auto b (cluster->routines.find (mu::string (U"b")));
	ASSERT_TRUE (b != cluster->routines.end ());
}

TEST (script_test, loads2)
{
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::loads::operation);
	ctx.push (new (GC) mu::script::string::node (mu::string (U"source_test.mujunk123")));
	auto valid (ctx ());
    ASSERT_TRUE (!valid);
}