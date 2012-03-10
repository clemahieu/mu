#include "operation.h"

#include <mu/core/errors/error_list.h>
#include <mu/script/loads/operation.h>
#include <mu/script/extensions/node.h>
#include <mu/script/string/node.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

void mu::script_test::loads::operation::run ()
{
	run_1 ();
}

void mu::script_test::loads::operation::run_1 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	mu::script::loads::operation loads;
	a1.push_back (boost::make_shared <mu::script::extensions::node> ());
	a1.push_back (boost::make_shared <mu::script::string::node> (std::wstring (L"source_test.mu")));
    auto ctx (mu::script::context (errors, a1, r1));
	loads (ctx);
    errors->print (std::wcout);
    assert (errors->errors.empty ());
	assert (r1.size () == 1);
	auto extensions (boost::dynamic_pointer_cast <mu::script::extensions::node> (r1 [0]));
	assert (extensions.get () != nullptr);
	assert (extensions->extensions->extensions_m.size () == 2);
	auto a (extensions->extensions->extensions_m.find (std::wstring (L"a")));
	assert (a != extensions->extensions->extensions_m.end ());
	auto b (extensions->extensions->extensions_m.find (std::wstring (L"b")));
	assert (b != extensions->extensions->extensions_m.end ());
}