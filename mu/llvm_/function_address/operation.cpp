#include "operation.h"

#include <mu/script/string/node.h>
#include <mu/core/errors/error_target.h>
#include <mu/llvm_/function/node.h>

#include <sstream>

void mu::llvm_::function_address::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		auto existing (remap.find (one->string));
		if (existing != remap.end ())
		{
			results.push_back (existing->second);
		}
		else
		{
			std::wstringstream message;
			message << L"Unable to find function named: ";
			message << one->string;
			(*errors_a) (message.str ());
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::llvm_::function_address::operation::count ()
{
	return 1;
}