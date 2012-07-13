#include <mu/core/errors/error_list.h>
#include <mu/script/loadb/operation.h>
#include <mu/script/string/node.h>
#include <mu/script/extensions/node.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/identity/operation.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, loadb1)
{
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::loadb::operation> ());
	auto valid (ctx ());
	EXPECT_EQ (!valid, true);
}

TEST (script_test, loadb2)
{
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
    auto windows_name (std::wstring (L"mu/binary_test/Debug/mu_binary_test.dll"));
    auto unix_name (std::wstring (L"mu/binary_test/Debug/libmu_binary_test.so"));
    auto osx_name (std::wstring (L"mu/binary_test/libmu_binary_test.so"));
    auto windows_path (boost::filesystem::initial_path() /= std::string (windows_name.begin (), windows_name.end ()));
    auto unix_path (boost::filesystem::initial_path () /= std::string (unix_name.begin (), unix_name.end ()));
    auto osx_path (boost::filesystem::initial_path () /= std::string (osx_name.begin (), osx_name.end ()));
    auto windows_exists (boost::filesystem::exists (windows_path));
    auto unix_exists (boost::filesystem::exists (unix_path));
    auto osx_exists (boost::filesystem::exists (osx_path));
    boost::shared_ptr <mu::script::string::node> file;
    if (windows_exists)
    {
        file = boost::make_shared <mu::script::string::node> (windows_name);
    }
    else if (unix_exists)
    {
        file = boost::make_shared <mu::script::string::node> (unix_name);
    }
    else if (osx_exists)
    {
        file = boost::make_shared <mu::script::string::node> (osx_name);
    }
    else
    {
        ASSERT_EQ (false, true);
    }
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::loadb::operation> ());
    ctx.push (file);
	auto valid (ctx ());
	ASSERT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
    auto ext (ctx.working (0));
	auto extensions (boost::dynamic_pointer_cast <mu::script::extensions::node> (ext));
	ASSERT_NE (extensions.get (), nullptr);
	EXPECT_EQ (extensions->extensions->extensions_m.size (), 1);
	auto existing (extensions->extensions->extensions_m.find (std::wstring (L"identity")));
	EXPECT_NE (existing, extensions->extensions->extensions_m.end ());
	auto value (boost::dynamic_pointer_cast <mu::io::analyzer::extensions::global> (existing->second));
	EXPECT_NE (value.get (), nullptr);
	auto identity (boost::dynamic_pointer_cast <mu::script::identity::operation> (value->node));
	EXPECT_NE (identity, nullptr);
}