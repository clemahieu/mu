#include "operation.h"

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

void mu::script_test::loadb::operation::run ()
{
	run_1 ();
	//run_2 ();
}

void mu::script_test::loadb::operation::run_1 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	mu::script::loadb::operation loadb;
	std::vector <boost::shared_ptr <mu::script::operation>> stack;
    auto ctx (mu::script::context (errors, a1, r1, stack));
	loadb (ctx);
	assert (!errors->errors.empty ());
}

void mu::script_test::loadb::operation::run_2 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
    auto windows_name (std::wstring (L"mu/binary_test/Debug/mu_binary_test.dll"));
    auto unix_name (std::wstring (L"mu/binary_test/Debug/libmu_binary_test.so"));
    auto windows_path (boost::filesystem::initial_path() /= std::string (windows_name.begin (), windows_name.end ()));
    auto unix_path (boost::filesystem::initial_path () /= std::string (unix_name.begin (), unix_name.end ()));
    auto windows_exists (boost::filesystem::exists (windows_path));
    auto unix_exists (boost::filesystem::exists (unix_path));
    boost::shared_ptr <mu::script::string::node> file;
    if (windows_exists)
    {
        file = boost::make_shared <mu::script::string::node> (windows_name);
    }
    else if (unix_exists)
    {
        file = boost::make_shared <mu::script::string::node> (unix_name);
    }
    else
    {
        assert (false && L"Unable to open windows or unix shared library");
    }
	a1.push_back (file);
	mu::script::loadb::operation loadb;
	std::vector <boost::shared_ptr <mu::script::operation>> stack;
    auto ctx (mu::script::context (errors, a1, r1, stack));
	loadb (ctx);
	assert (errors->errors.empty ());
	assert (r1.size () == 1);
	auto extensions (boost::dynamic_pointer_cast <mu::script::extensions::node> (r1 [0]));
	assert (extensions.get () != nullptr);
	assert (extensions->extensions->extensions_m.size () == 1);
	auto existing (extensions->extensions->extensions_m.find (std::wstring (L"identity")));
	assert (existing != extensions->extensions->extensions_m.end ());
	auto value (boost::dynamic_pointer_cast <mu::io::analyzer::extensions::global> (existing->second));
	assert (value.get () != nullptr);
	auto identity (boost::dynamic_pointer_cast <mu::script::identity::operation> (value->node));
	assert (identity != nullptr);
}