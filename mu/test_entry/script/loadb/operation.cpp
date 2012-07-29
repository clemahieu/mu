#include <mu/core/errors/error_list.h>
#include <mu/script/loadb/operation.h>
#include <mu/script/string/node.h>
#include <mu/script/extensions/node.h>
#include <mu/script/identity/operation.h>
#include <mu/script/context.h>
#include <mu/io/keywording/extensions.h>
#include <mu/io/keywording/global.h>
#include <mu/io/keywording/keywording.h>

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
    auto unix_name (mu::string (U"mu/binary_test/Debug/libmu_binary_test.so"));
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
        ASSERT_EQ (false, true);
    }
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::loadb::operation);
    ctx.push (file);
	auto valid (ctx ());
	ASSERT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
    auto ext (ctx.working (0));
	auto extensions (dynamic_cast <mu::script::extensions::node *> (ext));
	ASSERT_NE (extensions, nullptr);
	auto existing ((*extensions->extensions) (mu::string (U"identity")));
	EXPECT_TRUE (!existing.empty ());
}