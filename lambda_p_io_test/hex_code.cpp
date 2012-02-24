#include "hex_code.h"

#include <lambda_p_io_test/lexer_result.h>
#include <core/errors/error_list.h>
#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/source.h>

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

void lambda_p_io_test::hex_code::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_io_test::hex_code::run_1 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L":aq");
	source ();
	assert (result.results.empty ());
	assert (!errors->errors.empty ());
	auto e1 (errors->errors [0]);
	assert (e1.second == mu::core::context (1, 3, 2, 1, 3, 2));
}

void lambda_p_io_test::hex_code::run_2 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L":uq");
	source ();
	assert (result.results.empty ());
	assert (!errors->errors.empty ());
	auto e1 (errors->errors [0]);
	assert (e1.second == mu::core::context (1, 3, 2, 1, 3, 2));
}