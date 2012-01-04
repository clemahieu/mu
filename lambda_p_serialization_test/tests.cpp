#include "tests.h"

#include <lambda_p_serialization_test/wistream_input_test.h>
#include <lambda_p_serialization_test/istream_input_test.h>
#include <lambda_p_serialization_test/routine_builder_test.h>
#include <lambda_p_serialization_test/source.h>
#include <lambda_p_serialization_test/lexer.h>
#include <lambda_p_serialization_test/parser.h>
#include <lambda_p_serialization_test/analyzer.h>
#include <lambda_p_serialization_test/data.h>

void lambda_p_serialization_test::tests::run ()
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
		data test;
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
		routine_builder_test test;
		test.run ();
	}
}