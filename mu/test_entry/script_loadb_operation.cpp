#include <mu/core/errors/error_list.h>
#include <mu/script/loadb_operation.h>
#include <mu/script/string_node.h>
#include <mu/script/parser_scope_node.h>
#include <mu/script/identity.h>
#include <mu/script/context.h>
#include <mu/io/analyzer_extensions.h>
#include <mu/io/analyzer_global.h>
#include <mu/io/analyzer_analyzer.h>

#include <boost/filesystem.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, loadb1)
{
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::loadb::operation);
	auto valid (ctx ());
	EXPECT_EQ (!valid, true);
}

TEST (script_test, loadb2)
{
	mu::core::errors::error_list errors;
    auto windows_name (mu::string (U"mu/binary_test/Debug/mu_binary_test.dll"));
    auto unix_name (mu::string (U"mu/binary_test/libmu_binary_test.so"));
    auto osx_name (mu::string (U"mu/binary_test/Debug/libmu_binary_test.dylib"));
    auto windows_path (boost::filesystem::initial_path() /= std::string (windows_name.begin (), windows_name.end ()));
    auto unix_path (boost::filesystem::initial_path () /= std::string (unix_name.begin (), unix_name.end ()));
    auto osx_path (boost::filesystem::initial_path () /= std::string (osx_name.begin (), osx_name.end ()));
    auto windows_exists (boost::filesystem::exists (windows_path));
    auto unix_exists (boost::filesystem::exists (unix_path));
    auto osx_exists (boost::filesystem::exists (osx_path));
    mu::script::string::node * file;
    if (windows_exists)
    {
        file = new (GC) mu::script::string::node (windows_name);
    }
    else if (unix_exists)
    {
        file = new (GC) mu::script::string::node (unix_name);
    }
    else if (osx_exists)
    {
        file = new (GC) mu::script::string::node (osx_name);
    }
    else
    {
        ASSERT_TRUE (false);
    }
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::loadb::operation);
    ctx.push (file);
	auto valid (ctx ());
	ASSERT_TRUE (valid);
	EXPECT_TRUE (ctx.working_size () == 1);
    auto ext (ctx.working (0));
	auto extensions (dynamic_cast <mu::script::parser_scope::node *> (ext));
	ASSERT_TRUE (extensions != nullptr);
	auto existing (extensions->injected.find (mu::string (U"identity")));
	EXPECT_TRUE (existing != extensions->injected.end ());
}
