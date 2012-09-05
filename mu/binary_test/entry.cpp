#include <boost/cstdint.hpp>

#include <mu/script/parser_scope_node.h>
#include <mu/script/identity_operation.h>
#include <mu/io/analyzer_extensions.h>

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
	auto result (new (GC) mu::script::parser_scope::node);
	result->injected [mu::string (U"identity")] = new (GC) mu::script::identity::operation;
	return result;
}