#include "node.h"

#include <sstream>

std::wstring lambda_p_script::package::node::debug ()
{
	std::wstringstream contents;
	contents << L"lambda_p_script::package::node:";
	for (auto i (items.begin ()), j (items.end ()); i != j; ++i)
	{
		contents << '\n';
		contents << (*i).first;
	}
	return contents.str ();
}