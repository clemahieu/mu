#include "truncate.h"

#include <lambda_p_script/string/node.h>
#include <lambda_p_script/astring/node.h>

#include <boost/make_shared.hpp>

void lambda_p_script::astring::truncate::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_script::string::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		std::string string (one->string.begin (), one->string.end ());
		results.push_back (boost::make_shared <lambda_p_script::astring::node> (string));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_script::astring::truncate::count ()
{
	return 1;
}