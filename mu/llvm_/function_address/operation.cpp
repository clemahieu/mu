#include "operation.h"

#include <mu/script/runtime/routine.h>
#include <mu/core/errors/error_target.h>
#include <mu/llvm_/function/node.h>

#include <sstream>

void mu::llvm_::function_address::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::runtime::routine> (parameters [0]));
	if (one.get () != nullptr)
	{
		auto existing (remap.find (one));
		if (existing != remap.end ())
		{
			results.push_back (existing->second);
		}
		else
		{
			(*errors_a) (L"Routine has no address mapping");
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