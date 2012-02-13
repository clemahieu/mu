#include "index.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm/cluster/node.h>
#include <lambda_p_script/integer/node.h>
#include <lambda_p_llvm/value/node.h>

#include <sstream>

void lambda_p_llvm::cluster::index::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::cluster::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::integer::node> (parameters [1]));
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

size_t lambda_p_llvm::cluster::index::count ()
{
	return 2;
}