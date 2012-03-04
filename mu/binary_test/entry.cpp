#include <boost/cstdint.hpp>

#include <mu/io/analyzer.extensions.extensions.h>
#include <mu/script/extensions.node.h>
#include <mu/script/identity.operation.h>
#include <mu/io/analyzer.extensions.global.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

extern "C" boost::uint64_t version_554bc0f73fa23e91 = 0x6d6ecf1f10200f;

extern "C" boost::shared_ptr <mu::script::extensions::node> extensions ()
{
	auto result (boost::make_shared <mu::script::extensions::node> ());
	result->extensions->extensions_m [std::wstring (L"identity")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::identity::operation> ());
	return result;
}
