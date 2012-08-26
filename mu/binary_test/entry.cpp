#include <boost/cstdint.hpp>

#include <mu/script/extensions/node.h>
#include <mu/script/identity/operation.h>
#include <mu/io/keywording_extensions.h>

#include <gc_cpp.h>

extern "C"
#ifdef _WIN32
__declspec (dllexport)
#endif
boost::uint64_t version_554bc0f73fa23e91 = 0x6d6ecf1f10200f;

extern "C"
#ifdef _WIN32
__declspec (dllexport)
#endif
void * extensions ()
{
	auto result (new (GC) mu::script::extensions::node);
	(*result->extensions) (mu::string (U"identity"), new (GC) mu::script::identity::operation);
	return result;
}