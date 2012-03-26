#include <mu/script/package/node.h>

#include <sstream>

std::wstring mu::script::package::node::debug ()
{
	std::wstringstream contents;
	contents << L"mu::script::package::node:";
	for (auto i (items.begin ()), j (items.end ()); i != j; ++i)
	{
		contents << '\n';
		contents << (*i).first;
	}
	return contents.str ();
}