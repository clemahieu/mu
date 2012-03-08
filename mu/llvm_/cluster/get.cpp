#include "get.h"

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/cluster/node.h>
#include <mu/script/string/node.h>
#include <mu/llvm_/function/node.h>

#include <sstream>

void mu::llvm_::cluster::get::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::string::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto existing (one->names.find (two->string));
			if (existing != one->names.end ())
			{
				context_a.results.push_back (existing->second);
			}
			else
			{
				std::wstringstream message;
				message << L"Cluster has no routine named: ";
				message << two->string;
				(*context_a.errors) (message.str ());
			}
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [1], 1);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::cluster::get::count ()
{
	return 2;
}