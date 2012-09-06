#include <mu/llvm_/cluster_index.h>

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/cluster_node.h>
#include <mu/script/string_node.h>
#include <mu/llvm_/function_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <sstream>

bool mu::llvm_::cluster::index::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::llvm_::cluster::node, mu::script::string::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::cluster::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::string::node *> (context_a.parameters (1)));
        auto existing (one->routines.find (two->string));
		if (existing != one->routines.end ())
		{
			context_a.push (existing->second);
		}
		else
		{
			mu::stringstream message;
			message << U"Cluster does not have routine named: ";
			message << two->string;
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}