#include <mu/script_test/loads/operation.h>

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
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::loads::operation> ());
	ctx.push (boost::make_shared <mu::script::extensions::node> ());
	ctx.push (boost::make_shared <mu::script::string::node> (std::wstring (L"source_test.mu")));
	auto valid (ctx ());
	errors.target->print (std::wcout);
    assert (valid);
	assert (ctx.working_size () == 1);
	auto extensions (boost::dynamic_pointer_cast <mu::script::extensions::node> (ctx.working (0)));
	assert (extensions.get () != nullptr);
	assert (extensions->extensions->extensions_m.size () == 2);
	auto a (extensions->extensions->extensions_m.find (std::wstring (L"a")));
	assert (a != extensions->extensions->extensions_m.end ());
	auto b (extensions->extensions->extensions_m.find (std::wstring (L"b")));
	assert (b != extensions->extensions->extensions_m.end ());
}