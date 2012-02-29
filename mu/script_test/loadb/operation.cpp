#include "operation.h"

#include <mu/core/errors/error_list.h>
#include <mu/script/loadb/operation.h>
#include <mu/script/string/node.h>
#include <mu/script/extensions/node.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/identity/operation.h>

#include <boost/make_shared.hpp>

void mu::script_test::loadb::operation::run ()
{
	run_1 ();
	run_2 ();
}

void mu::script_test::loadb::operation::run_1 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	mu::script::loadb::operation loadb;
	loadb.perform (errors, a1, r1);
	assert (!errors->errors.empty ());
}

void mu::script_test::loadb::operation::run_2 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	auto file (boost::make_shared <mu::script::string::node> (std::wstring (L"x64/Debug/mu_binary_test.dll")));
	a1.push_back (file);
	mu::script::loadb::operation loadb;
	loadb.perform (errors, a1, r1);
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