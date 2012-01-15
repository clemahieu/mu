#include "operation.h"

#include <lambda_p_script/times/operation.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_script/integer/subtract.h>
#include <lambda_p_script/integer/node.h>
#include <lambda_p_script_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p_script/routine.h>

#include <boost/bind.hpp>

void lambda_p_script_test::times::operation::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_script_test::times::operation::run_1 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_script::times::operation times;
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n1 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (0)));
	arguments.push_back (n1);
	auto n2 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::subtract));
	arguments.push_back (n2);
	auto n3 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (5)));
	arguments.push_back (n3);
	auto n4 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (1)));
	arguments.push_back (n4);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	times.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 2);
	assert (results [0] == n3);
	assert (results [1] == n4);
}

void lambda_p_script_test::times::operation::run_2 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~; subtract number amount] subtract [subtract number amount] amount]");
	assert (builder.errors->errors.empty ());
	lambda_p_script::times::operation times;
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n1 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (2)));
	arguments.push_back (n1);
	auto n2 (builder.routines [0]);
	arguments.push_back (n2);
	auto n3 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::subtract));
	arguments.push_back (n3);
	auto n4 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (5)));
	arguments.push_back (n4);
	auto n5 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (1)));
	arguments.push_back (n5);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	times.perform (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 3);
	auto r1 (boost::dynamic_pointer_cast <lambda_p_script::integer::subtract> (results [0]));
	assert (r1.get () != nullptr);
	auto r2 (boost::dynamic_pointer_cast <lambda_p_script::integer::node> (results [1]));
	assert (r2.get () != nullptr);
	assert (r2->value == 3);
	auto r3 (boost::dynamic_pointer_cast <lambda_p_script::integer::node> (results [2]));
	assert (r3.get () != nullptr);
	assert (r3->value == 1);
}