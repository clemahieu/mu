#include <mu/io/analyzer/extensions/extensions.h>

mu::io::analyzer::extensions::extensions::extensions ()
{
}

mu::io::analyzer::extensions::extensions::~extensions ()
{
}

mu::io::analyzer::extensions::extensions::extensions (std::map <std::wstring, mu::io::analyzer::extensions::extension *> extensions_a)
	: extensions_m (extensions_a)
{
}