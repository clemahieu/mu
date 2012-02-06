#include "builder.h"

#include <lambda_p_script_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script/identity/operation.h>
#include <lambda_p_script/integer/node.h>
#include <lambda_p_script/string/node.h>
#include <lambda_p_script/call.h>
#include <lambda_p_script/expression.h>
#include <lambda_p_script/reference.h>
#include <lambda_p_script/constant.h>
#include <lambda_p_script/parameters.h>
#include <lambda_p/segment.h>
#include <lambda_p_script/cluster/node.h>

#include <boost/bind.hpp>

void lambda_p_script_io_test::builder::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
	run_8 ();
	run_9 ();
}

void lambda_p_script_io_test::builder::run_1 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
}

void lambda_p_script_io_test::builder::run_2 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	source ();
	auto cluster (builder.clusters [0]);
	auto routine (cluster->routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	auto n1 (boost::shared_ptr <lambda_p_script::identity::operation> (new lambda_p_script::identity::operation));
	arguments.push_back (n1);
	auto n2 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (n2);
	routine->perform (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 2);
	assert (boost::dynamic_pointer_cast <lambda_p_script::identity::operation> (results [0]).get () != nullptr);
	assert (results [1] == n2);
}

void lambda_p_script_io_test::builder::run_3 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	source ();
	auto cluster (builder.clusters [0]);
	auto routine (cluster->routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	auto n1 (boost::shared_ptr <lambda_p_script::identity::operation> (new lambda_p_script::identity::operation));
	arguments.push_back (n1);
	routine->perform (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == n1);
}

void lambda_p_script_io_test::builder::run_4 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	source ();
	auto cluster (builder.clusters [0]);
	auto routine (cluster->routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine->perform (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 0);
}

void lambda_p_script_io_test::builder::run_5 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~] # d4]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n1 (boost::shared_ptr <lambda_p_script::identity::operation> (new lambda_p_script::identity::operation));
	arguments.push_back (n1);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine->perform (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 1);
	auto number (boost::dynamic_pointer_cast <lambda_p_script::integer::node> (results [0]));
	assert (number.get () != nullptr);
	assert (number->value == 4);
}

void lambda_p_script_io_test::builder::run_6 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~] ` testing]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n1 (boost::shared_ptr <lambda_p_script::identity::operation> (new lambda_p_script::identity::operation));
	arguments.push_back (n1);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine->perform (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 1);
	auto data (boost::dynamic_pointer_cast <lambda_p_script::string::node> (results [0]));
	assert (data.get () != nullptr);
	assert (data->string == std::wstring (L"testing"));
}

void lambda_p_script_io_test::builder::run_7 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~] ` |%|string with spaces%]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n1 (boost::shared_ptr <lambda_p_script::identity::operation> (new lambda_p_script::identity::operation));
	arguments.push_back (n1);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine->perform (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 1);
	auto data (boost::dynamic_pointer_cast <lambda_p_script::string::node> (results [0]));
	assert (data.get () != nullptr);
	assert (data->string == std::wstring (L"string with spaces"));
}

void lambda_p_script_io_test::builder::run_8 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~; #] ;; 1]");
	source ();
	assert (!builder.errors->errors.empty ());
}

void lambda_p_script_io_test::builder::run_9 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~; a b c] .id a [a b c] c]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
	assert (routine->calls.size () == 3);
	auto c1 (routine->calls [0]); // [:~; a b c]
	assert (c1->results == 0);
	assert (c1->arguments.size () == 1);
	auto c11 (boost::dynamic_pointer_cast <lambda_p_script::parameters> (c1->arguments [0]));
	assert (c11.get () != nullptr);
	auto c2 (routine->calls [1]); // [a b c]
	assert (c2->results == 1);
	assert (c2->arguments.size () == 3);
	auto c21 (boost::dynamic_pointer_cast <lambda_p_script::reference> (c2->arguments [0]));
	assert (c21.get () != nullptr);
	assert (c21->expression == 0);
	assert (c21->index == 0);
	auto c22 (boost::dynamic_pointer_cast <lambda_p_script::reference> (c2->arguments [1]));
	assert (c22.get () != nullptr);
	assert (c22->expression == 0);
	assert (c22->index == 1);
	auto c23 (boost::dynamic_pointer_cast <lambda_p_script::reference> (c2->arguments [2]));
	assert (c23.get () != nullptr);
	assert (c23->expression == 0);
	assert (c23->index == 2);
	auto c3 (routine->calls [2]); // .id a [a b c] c
	assert (c3->results == 2);
	assert (c3->arguments.size () == 4);
	auto c31 (boost::dynamic_pointer_cast <lambda_p_script::constant> (c3->arguments [0]));
	assert (c31.get () != nullptr);
	auto c32 (boost::dynamic_pointer_cast <lambda_p_script::reference> (c3->arguments [1]));
	assert (c32.get () != nullptr);
	assert (c32->expression == 0);
	assert (c32->index == 0);
	auto c33 (boost::dynamic_pointer_cast <lambda_p_script::expression> (c3->arguments [2]));
	assert (c33.get () != nullptr);
	assert (c33->index == 1);
	auto c34 (boost::dynamic_pointer_cast <lambda_p_script::reference> (c3->arguments [3]));
	assert (c34->index == 2);
	assert (c34->expression == 0);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	auto n1 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::identity::operation));
	arguments.push_back (n1);
	auto n2 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (n2);
	auto n3 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (n3);
	routine->perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 4);
	assert (results [0] == n1);
	assert (results [1] == n2);
	assert (results [2] == n3);
	assert (results [3] == n3);
}