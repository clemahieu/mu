#include <boost/cstdint.hpp>

#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/extensions/node.h>
#include <mu/script/identity/operation.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/debugging/flat_mapping.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

extern "C"
#ifdef _WIN32
__declspec (dllexport)
#endif
boost::uint64_t version_554bc0f73fa23e91 = 0x6d6ecf1f10200f;

extern "C"
#ifdef _WIN32
__declspec (dllexport)
#endif
void extensions (mu::script::extensions::node ** extensions, mu::script::debugging::mapping ** debug_info_a)
{
	auto result (new mu::script::extensions::node);
	result->extensions->extensions_m [std::wstring (L"identity")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::identity::operation> ());
	*extensions = result;
	auto debug_info (new mu::script::debugging::flat_mapping);
	*debug_info_a = debug_info;
}