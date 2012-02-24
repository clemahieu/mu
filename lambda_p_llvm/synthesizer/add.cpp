#include "add.h"

#include <io/analyzer/extensions/extensions.h>
#include <io/analyzer/extensions/global.h>
#include <lambda_p_llvm/synthesizer/operation.h>
#include <lambda_p_script/string/node.h>

#include <boost/make_shared.hpp>

void lambda_p_llvm::synthesizer::add::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::synthesizer::operation> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::string::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			one->analyzer.extensions->extensions_m [two->string] = boost::make_shared <mu::io::analyzer::extensions::global> (parameters [2]);
		}
		else
		{
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::synthesizer::add::count ()
{
	return 3;
}

std::wstring lambda_p_llvm::synthesizer::add::name ()
{
	return std::wstring (L"lambda_p_llvm::synthesizer::add");
}