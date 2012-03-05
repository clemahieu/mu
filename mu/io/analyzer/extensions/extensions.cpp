#include "extensions.h"

mu::io::analyzer::extensions::extensions::extensions ()
{
}

mu::io::analyzer::extensions::extensions::extensions (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>> extensions_a)
	: extensions_m (extensions_a)
{
}