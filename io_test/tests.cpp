#include "tests.h"

#include <io_test/wistream_input_test.h>
#include <io_test/istream_input_test.h>
#include <io_test/source.h>
#include <io_test/lexer.h>
#include <io_test/parser.h>
#include <io_test/analyzer.h>
#include <io_test/extension.h>
#include <io_test/builder.h>
#include <io_test/complex_identifier.h>
#include <io_test/control.h>
#include <io_test/hex_code.h>
#include <io_test/multiline_comment.h>
#include <io_test/begin.h>
#include <io_test/values.h>
#include <io_test/single.h>
#include <io_test/full.h>
#include <io_test/routine.h>

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