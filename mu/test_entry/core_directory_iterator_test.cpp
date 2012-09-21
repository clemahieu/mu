#include <boost/filesystem.hpp>

#include <gtest/gtest.h>

TEST (core_test, directory_iterator_test1)
{
    auto failed (false);
    try
    {
        auto path (boost::filesystem::initial_path () /= L"examples");
        boost::filesystem::directory_iterator i (path);
    }
    catch (...)
    {
        failed = true;
    }
    EXPECT_EQ (failed, false);
}

// Test iterating a file, which should fail
TEST (core_test, directory_iterator_test2)
{
    auto failed (false);
	auto path (boost::filesystem::initial_path () /= L"examples/test.mu");
	try
	{
		boost::filesystem::directory_iterator i (path);
        EXPECT_EQ (false, true);
	}
	catch (boost::filesystem::filesystem_error & error)
	{
		failed = true;
	}
    EXPECT_EQ (failed, true);
}

TEST (core_test, directory_iterator_test3)
{
	auto path (boost::filesystem::initial_path () /= L"examples");
	for (boost::filesystem::directory_iterator i (path); i != boost::filesystem::directory_iterator (); ++i)
	{
	}
}