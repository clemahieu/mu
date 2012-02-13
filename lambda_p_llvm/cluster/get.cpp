#include "get.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm/cluster/node.h>
#include <lambda_p_script/string/node.h>
#include <lambda_p_llvm/value/node.h>

#include <sstream>

void lambda_p_llvm::cluster::get::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::string::node> (parameters [1]));
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

size_t lambda_p_llvm::cluster::get::count ()
{
	return 2;
}