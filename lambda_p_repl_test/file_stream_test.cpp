#include "file_stream_test.h"

#include <lambda_p_repl/file_stream.h>

#include <boost/filesystem.hpp>

void lambda_p_repl_test::file_stream_test::run ()
{
	run_1 ();
}

void lambda_p_repl_test::file_stream_test::run_1 ()
{
	auto path (boost::filesystem::initial_path () /= L"junkfile0239840289374");
	lambda_p_repl::file_stream stream (path.wstring ());
	wchar_t val (stream ());
	assert (val == ~0);
}