#include <mu/script/extensions/node.h>

#include <mu/io/keywording_extensions.h>

#include <gc_cpp.h>

mu::script::extensions::node::node ()
	: extensions (new (GC) mu::io::keywording::extensions)
{
}

mu::script::extensions::node::node (mu::io::keywording::extensions * extensions_a)
	: extensions (extensions_a)
{
}

mu::string mu::script::extensions::node::name ()
{
	return mu::string (U"mu::script::extensions::node");
}