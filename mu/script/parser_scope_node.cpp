#include <mu/script/parser_scope_node.h>

#include <mu/io/analyzer_extensions.h>

#include <gc_cpp.h>

mu::script::parser_scope::node::node ():
extensions (new (GC) mu::io::keywording::extensions)
{
}

mu::script::parser_scope::node::node (mu::io::keywording::extensions * extensions_a):
extensions (extensions_a)
{
}

mu::string mu::script::parser_scope::node::name ()
{
	return mu::string (U"mu::script::parser_scope::node");
}