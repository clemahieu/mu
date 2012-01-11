#include "operation.h"

#include <lambda_p_script/times/operation.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_script/integer/subtract.h>
#include <lambda_p_script/integer/node.h>

#include <boost/bind.hpp>

void lambda_p_script_test::times::operation::run ()
{
	run_1 ();
}

void lambda_p_script_test::times::operation::run_1 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_script::times::operation times;
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n1 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (2)));
	auto n2 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::subtract));
	auto n3 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (5)));
	auto n4 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (1)));
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	times.perform (errors, arguments, results);
}