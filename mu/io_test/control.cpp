#include <mu/io_test/control.h>

#include <mu/io_test/lexer_result.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/source.h>

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

void mu::io_test::control::run ()
{
	run_1 ();
	run_2 ();
}

void mu::io_test::control::run_1 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":");
	lexer ();
	assert (result.results.empty ());
	assert (!errors->errors.empty ());
}

void mu::io_test::control::run_2 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":0");
	lexer ();
	assert (result.results.empty ());
	assert (!errors->errors.empty ());
}