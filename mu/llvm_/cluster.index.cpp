#include <mu/llvm_/cluster.index.h>

#include <mu/core/errors.error_list.h>
#include <mu/llvm_/cluster.node.h>
#include <mu/script/integer.node.h>
#include <mu/llvm_/function.node.h>

#include <sstream>

void mu::llvm_::cluster::index::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::integer::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (one->routines.size () > two->value)
			{
				results.push_back (one->routines [two->value]);
			}
			else
			{
				std::wstringstream message;
				message << L"Cluster only has: ";
				message << one->routines.size ();
				message << L" routines: ";
				message << two->value;
				(*errors_a) (message.str ());
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

size_t mu::llvm_::cluster::index::count ()
{
	return 2;
}
