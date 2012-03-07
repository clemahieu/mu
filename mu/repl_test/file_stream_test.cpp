#include "file_stream_test.h"

#include <mu/repl/file_stream.h>

#include <boost/filesystem.hpp>

void mu::repl_test::file_stream_test::run ()
{
	run_1 ();
}

void mu::repl_test::file_stream_test::run_1 ()
{
	auto path (boost::filesystem::initial_path () /= L"junkfile0239840289374");
	mu::repl::file_stream stream (path.wstring ());
	wchar_t val (stream ());
	assert (val == (wchar_t) (~0));
}