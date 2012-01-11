#include "builder.h"

#include <lambda_p_script_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script/operations/identity.h>
#include <lambda_p_script/integer/node.h>
#include <lambda_p_script/data/node.h>

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
}

void lambda_p_script_io_test::builder::run_1 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 1);
}

void lambda_p_script_io_test::builder::run_2 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	auto routine (builder.routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	auto n1 (boost::shared_ptr <lambda_p_script::operations::identity> (new lambda_p_script::operations::identity));
	arguments.push_back (n1);
	auto n2 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (n2);
	routine->perform (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == n2);
}

void lambda_p_script_io_test::builder::run_3 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	auto routine (builder.routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	auto n1 (boost::shared_ptr <lambda_p_script::operations::identity> (new lambda_p_script::operations::identity));
	arguments.push_back (n1);
	routine->perform (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 0);
}

void lambda_p_script_io_test::builder::run_4 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	auto routine (builder.routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine->perform (builder.errors, arguments, results);
	assert (!builder.errors->errors.empty ());
}

void lambda_p_script_io_test::builder::run_5 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~ # d4]");
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 1);
	auto routine (builder.routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n1 (boost::shared_ptr <lambda_p_script::operations::identity> (new lambda_p_script::operations::identity));
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
	source (L"[:~ ` testing]");
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 1);
	auto routine (builder.routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n1 (boost::shared_ptr <lambda_p_script::operations::identity> (new lambda_p_script::operations::identity));
	arguments.push_back (n1);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine->perform (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 1);
	auto data (boost::dynamic_pointer_cast <lambda_p_script::data::node> (results [0]));
	assert (data.get () != nullptr);
	assert (data->string == std::wstring (L"testing"));
}

void lambda_p_script_io_test::builder::run_7 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~ ` |%|string with spaces%]");
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 1);
	auto routine (builder.routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n1 (boost::shared_ptr <lambda_p_script::operations::identity> (new lambda_p_script::operations::identity));
	arguments.push_back (n1);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine->perform (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 1);
	auto data (boost::dynamic_pointer_cast <lambda_p_script::data::node> (results [0]));
	assert (data.get () != nullptr);
	assert (data->string == std::wstring (L"string with spaces"));
}

void lambda_p_script_io_test::builder::run_8 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~; #]]");
	assert (!builder.errors->errors.empty ());
}