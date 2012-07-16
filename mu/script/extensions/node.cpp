#include <mu/script/extensions/node.h>

#include <mu/io/analyzer/extensions/extensions.h>

#include <gc_cpp.h>

mu::script::extensions::node::node ()
	: extensions (new (GC) mu::io::analyzer::extensions::extensions)
{
}

mu::script::extensions::node::node (mu::io::analyzer::extensions::extensions * extensions_a)
	: extensions (extensions_a)
{
}

mu::string mu::script::extensions::node::name ()
{
	return mu::string (U"mu::script::extensions::node");
}