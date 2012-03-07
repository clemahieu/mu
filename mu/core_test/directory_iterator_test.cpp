#include "directory_iterator_test.h"

#include <boost/filesystem.hpp>

void mu::core_test::directory_iterator_test::run ()
{
	//run_1 ();
	run_2 ();
	run_3 ();
}

void mu::core_test::directory_iterator_test::run_1 ()
{
	auto path (boost::filesystem::initial_path () /= L"examples");
	boost::filesystem3::directory_iterator i (path);
}

void mu::core_test::directory_iterator_test::run_2 ()
{
	auto path (boost::filesystem::initial_path () /= L"examples/test.lp");
	try
	{
		boost::filesystem3::directory_iterator i (path);
		assert (false && L"iterating a file");
	}
	catch (boost::filesystem3::filesystem_error & error)
	{
		if (1 == 1) assert (true);
	}
}

void mu::core_test::directory_iterator_test::run_3 ()
{
	auto path (boost::filesystem::initial_path () /= L"examples");
	for (boost::filesystem3::directory_iterator i (path); i != boost::filesystem3::directory_iterator (); ++i)
	{
		if (1 == 1)	assert (true);
	}
}