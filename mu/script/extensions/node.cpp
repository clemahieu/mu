#include "node.h"

#include <mu/io/analyzer/extensions/extensions.h>

#include <boost/make_shared.hpp>

mu::script::extensions::node::node ()
	: extensions (boost::make_shared <mu::io::analyzer::extensions::extensions> ())
{
}

mu::script::extensions::node::node (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: extensions (extensions_a)
{
}

std::wstring mu::script::extensions::node::name ()
{
	return std::wstring (L"mu::script::extensions::node");
}