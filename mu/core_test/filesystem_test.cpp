#include "filesystem_test.h"

#include <boost/filesystem.hpp>

#include <fstream>

void mu::core_test::filesystem_test::run ()
{
	run_1 ();
	run_2 ();
}

void mu::core_test::filesystem_test::run_1 ()
{
	auto path (::boost::filesystem::initial_path ());
	path /= L"test";
	path /= L"test";
}

void mu::core_test::filesystem_test::run_2 ()
{
	auto path (boost::filesystem::initial_path ());
	path /= L"examples";
	path /= L"test.lp";
	std::ifstream stream;
	std::string str (path.string ());
	stream.open (str);
	assert (stream.is_open () && "Set project working directory to $(SolutionDir)");
}
