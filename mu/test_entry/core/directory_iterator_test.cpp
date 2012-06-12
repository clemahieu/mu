#include <boost/filesystem.hpp>

#include <gtest/gtest.h>

TEST (core_test, directory_iterator_test1)
{
    auto failed (false);
    try
    {
        auto path (boost::filesystem::initial_path () /= L"examples");
        boost::filesystem3::directory_iterator i (path);
    }
    catch (...)
    {
        failed = true;
    }
    EXPECT_EQ (failed, false);
}

TEST (core_test, directory_iterator_test2)
{
    auto failed (false);
	auto path (boost::filesystem::initial_path () /= L"examples/test.lp");
	try
	{
		boost::filesystem3::directory_iterator i (path);
	}
	catch (boost::filesystem3::filesystem_error & error)
	{
		failed = true;
	}
    EXPECT_EQ (failed, false);
}

TEST (core_test, directory_iterator_test3)
{
	auto path (boost::filesystem::initial_path () /= L"examples");
	for (boost::filesystem3::directory_iterator i (path); i != boost::filesystem3::directory_iterator (); ++i)
	{
	}
}