#include "store.h"

#include <mu/llvm_/basic_block/node.h>

void mu::llvm_::basic_block::store::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::basic_block::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::basic_block::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			one->block = two->block;
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

size_t mu::llvm_::basic_block::store::count ()
{
	return 2;
}