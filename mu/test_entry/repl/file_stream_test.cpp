#include <mu/repl/file_stream.h>

#include <boost/filesystem.hpp>

#include <gtest/gtest.h>

TEST (repl_test, file_stream_test1)
{
	auto path (boost::filesystem::initial_path () /= L"junkfile0239840289374");
	mu::repl::file_stream stream (path.wstring ());
	wchar_t val (stream ());
	EXPECT_EQ (val, (wchar_t) (~0));
}