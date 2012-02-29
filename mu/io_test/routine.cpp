#include "routine.h"

#include <mu/io_test/analyzer_result.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/parser/parser.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/io/source.h>

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

void mu::io_test::routine::run ()
{
	run_1 ();
}

void mu::io_test::routine::run_1 ()
{
	mu::io_test::analyzer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::analyzer::analyzer analyzer (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), errors);
	mu::io::parser::parser parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2));
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator (), &lexer, _1));
	source (L"[unresolved ;; 1]");
	source ();
	assert (result.clusters.empty ());
	assert (!errors->errors.empty ());
	auto e1 (errors->errors [0]);
	assert (e1.second == mu::core::context (1, 2, 1, 1, 11, 10));
}