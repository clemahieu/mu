#include "filesystem_test.h"

#include <boost/filesystem.hpp>

#include <fstream>

void lambda_p_test::filesystem_test::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_test::filesystem_test::run_1 ()
{
	auto path (::boost::filesystem::initial_path ());
	path /= L"test";
	path /= L"test";
}

void lambda_p_test::filesystem_test::run_2 ()
{
	auto path (boost::filesystem::initial_path ());
	path /= L"examples";
	path /= L"test.lp";
	std::ifstream stream;
	std::string str (path.string ());
	stream.open (str);
	assert (stream.is_open ());
}