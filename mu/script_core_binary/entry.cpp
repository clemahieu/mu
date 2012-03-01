#include <boost/cstdint.hpp>

#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/extensions/node.h>
#include <mu/script/string/extension.h>
#include <mu/script/astring/extension.h>
#include <mu/script/integer/extension.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/identity/operation.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

boost::uint64_t version_554bc0f73fa23e91 = 0x6d6ecf1f10200f;

boost::shared_ptr <mu::script::extensions::node> extensions ()
{
	auto result (boost::make_shared <mu::script::extensions::node> ());
	result->extensions->extensions_m [std::wstring (L"~")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::identity::operation> ());
	result->extensions->extensions_m [std::wstring (L"`")] = boost::make_shared <mu::script::string::extension> ();
	result->extensions->extensions_m [std::wstring (L"`a")] = boost::make_shared <mu::script::astring::extension> ();
	result->extensions->extensions_m [std::wstring (L"#")] = boost::make_shared <mu::script::integer::extension> ();
	return result;
}