#include "merge.h"

#include <boost/make_shared.hpp>

#include <lambda_p_io/analyzer/extensions/extensions.h>
#include <lambda_p_io/analyzer/extensions/global.h>
#include <lambda_p_llvm/synthesizer/operation.h>
#include <lambda_p_script/string/node.h>
#include <lambda_p_llvm/cluster/node.h>
#include <lambda_p_llvm/function/node.h>

void lambda_p_llvm::synthesizer::merge::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::synthesizer::operation> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::string::node> (parameters [1]));
	auto three (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (parameters [2]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (three.get () != nullptr)
			{
				for (auto i (three->names.begin ()), j (three->names.end ()); i != j; ++i)
				{
					std::wstring name (two->string.begin (), two->string.end ());
					name.append (i->first);
					one->analyzer.extensions->extensions_m [name] = boost::make_shared <lambda_p_io::analyzer::extensions::global> (i->second);
				}
			}
			else
			{
				invalid_type (errors_a, parameters [2], 2);
			}
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

size_t lambda_p_llvm::synthesizer::merge::count ()
{
	return 3;
}