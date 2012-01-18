#include "extensions.h"

lambda_p_io::analyzer::extensions::extensions::extensions ()
{
}

lambda_p_io::analyzer::extensions::extensions::extensions (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>> extensions_a)
	: extensions_m (extensions_a)
{
}