#include "tests.h"

#include <mu/io_test/wistream_input_test.h>
#include <mu/io_test/istream_input_test.h>
#include <mu/io_test/source.h>
#include <mu/io_test/lexer.h>
#include <mu/io_test/parser.h>
#include <mu/io_test/analyzer.h>
#include <mu/io_test/extension.h>
#include <mu/io_test/builder.h>
#include <mu/io_test/complex_identifier.h>
#include <mu/io_test/control.h>
#include <mu/io_test/hex_code.h>
#include <mu/io_test/multiline_comment.h>
#include <mu/io_test/begin.h>
#include <mu/io_test/values.h>
#include <mu/io_test/single.h>
#include <mu/io_test/full.h>
#include <mu/io_test/routine.h>

void mu::io_test::tests::run ()
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
}