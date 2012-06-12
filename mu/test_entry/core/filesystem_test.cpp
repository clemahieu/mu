#include <boost/filesystem.hpp>

#include <fstream>

#include <gtest/gtest.h>

TEST (core_test, filesystem_test1)
{
	auto path (::boost::filesystem::initial_path ());
	path /= L"test";
	path /= L"test";
}

TEST (core_test, filesystem_test2)
{
	auto path (boost::filesystem::initial_path ());
	path /= L"examples";
	path /= L"test.mu";
	std::ifstream stream;
	std::string str (path.string ());
	stream.open (str.c_str ());
	EXPECT_EQ (stream.is_open (), true);
}
