#include <mu/script/extensions/node.h>

#include <mu/io/analyzer/extensions/extensions.h>

#include <boost/make_shared.hpp>

#include <gc_cpp.h>

mu::script::extensions::node::node ()
	: extensions (new (GC) mu::io::analyzer::extensions::extensions)
{
}

mu::script::extensions::node::node (mu::io::analyzer::extensions::extensions * extensions_a)
	: extensions (extensions_a)
{
}

std::wstring mu::script::extensions::node::name ()
{
	return std::wstring (L"mu::script::extensions::node");
}