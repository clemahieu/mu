#include "tests.h"

#include <lambda_p_io_test/wistream_input_test.h>
#include <lambda_p_io_test/istream_input_test.h>
#include <lambda_p_io_test/source.h>
#include <lambda_p_io_test/lexer.h>
#include <lambda_p_io_test/parser.h>
#include <lambda_p_io_test/analyzer.h>
#include <lambda_p_io_test/extension.h>

void lambda_p_io_test::tests::run ()
{
	{
		source test;
		test.run ();
	}
	{
		lexer test;
		test.run ();
	}
	{
		parser test;
		test.run ();
	}
	{
		analyzer test;
		test.run ();
	}
	{
		extension test;
		test.run ();
	}
	{
		wistream_input_test test;
		test.run ();
	}
	{
		istream_input_test test;
		test.run ();
	}
}