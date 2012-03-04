#include <mu/llvm_/cluster.get.h>

#include <mu/core/errors.error_list.h>
#include <mu/llvm_/cluster.node.h>
#include <mu/script/string.node.h>
#include <mu/llvm_/function.node.h>

#include <sstream>

void mu::llvm_::cluster::get::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto existing (one->names.find (two->string));
			if (existing != one->names.end ())
			{
				results.push_back (existing->second);
			}
			else
			{
				std::wstringstream message;
				message << L"Cluster has no routine named: ";
				message << two->string;
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

size_t mu::llvm_::cluster::get::count ()
{
	return 2;
}
