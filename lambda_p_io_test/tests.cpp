#include "tests.h"

#include <lambda_p_io_test/wistream_input_test.h>
#include <lambda_p_io_test/istream_input_test.h>
#include <lambda_p_io_test/source.h>
#include <lambda_p_io_test/lexer.h>
#include <lambda_p_io_test/parser.h>
#include <lambda_p_io_test/analyzer.h>
#include <lambda_p_io_test/extension.h>
#include <lambda_p_io_test/builder.h>
#include <lambda_p_io_test/lambda.h>
#include <lambda_p_io_test/complex_identifier.h>
#include <lambda_p_io_test/control.h>
#include <lambda_p_io_test/hex_code.h>
#include <lambda_p_io_test/multiline_comment.h>
#include <lambda_p_io_test/begin.h>
#include <lambda_p_io_test/values.h>
#include <lambda_p_io_test/single.h>
#include <lambda_p_io_test/full.h>
#include <lambda_p_io_test/routine.h>
#include <lambda_p_io_test/ast.h>

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
	{
		builder test;
		test.run ();
	}
	{
		lambda test;
		test.run ();
	}
	{
		complex_identifier test;
		test.run ();
	}
	{
		control test;
		test.run ();
	}
	{
		hex_code test;
		test.run ();
	}
	{
		multiline_comment test;
		test.run ();
	}
	{
		begin test;
		test.run ();
	}
	{
		values test;
		test.run ();
	}
	{
		single test;
		test.run ();
	}
	{
		full test;
		test.run ();
	}
	{
		routine test;
		test.run ();
	}
	{
		ast test;
		test.run ();
	}
}