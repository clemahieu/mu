#include <mu/llvm_/cluster/get.h>

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/cluster/node.h>
#include <mu/script/string/node.h>
#include <mu/llvm_/function/node.h>
#include <mu/script/check.h>

#include <sstream>

bool mu::llvm_::cluster::get::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::cluster::node, mu::script::string::node> () (context_a));
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
			std::wstringstream message;
			message << L"Cluster has no routine named: ";
			message << two->string;
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}