#include <mu/script/package_node.h>

#include <sstream>

mu::string mu::script::package::node::debug ()
{
	mu::stringstream contents;
	contents << U"mu::script::package::node:";
	for (auto i (items.begin ()), j (items.end ()); i != j; ++i)
	{
		contents << '\n';
		contents << (*i).first;
	}
	return contents.str ();
}