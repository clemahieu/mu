#include "add.h"

#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/llvm_/synthesizer/operation.h>
#include <mu/script/string/node.h>

#include <boost/make_shared.hpp>

void mu::llvm_::synthesizer::add::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::synthesizer::operation> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [1]));
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

size_t mu::llvm_::synthesizer::add::count ()
{
	return 3;
}

std::wstring mu::llvm_::synthesizer::add::name ()
{
	return std::wstring (L"mu::llvm_::synthesizer::add");
}