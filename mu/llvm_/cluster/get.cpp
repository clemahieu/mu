#include <mu/llvm_/cluster/get.h>

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/cluster/node.h>
#include <mu/script/string_node.h>
#include <mu/llvm_/function/node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <sstream>

#include <assert.h>

bool mu::llvm_::cluster::get::operator () (mu::script::context & context_a)
{
    assert (false);
/*	bool result (mu::core::check <mu::llvm_::cluster::node, mu::script::string::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::cluster::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::string::node *> (context_a.parameters (1)));
		auto existing (one->names.find (two->string));
		if (existing != one->names.end ())
		{
			context_a.push (existing->second);
		}
		else
		{
			mu::stringstream message;
			message << L"Cluster has no routine named: ";
			message << two->string;
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;*/
}