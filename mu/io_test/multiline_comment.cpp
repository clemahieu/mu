#include "multiline_comment.h"

#include <mu/io_test/lexer_result.h>
#include <mu/core/errors.error_list.h>
#include <mu/io/lexer.lexer.h>
#include <mu/io/source.h>

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

void mu::io_test::multiline_comment::run ()
{
	run_1 ();
}

void mu::io_test::multiline_comment::run_1 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator (), &lexer, _1));
	source (L":[");
	source ();
	assert (result.results.empty ());
	assert (!errors->errors.empty ());
	auto e1 (errors->errors [0]);
	assert (e1.second == mu::core::context (1, 3, 2, 1, 3, 2));
}
