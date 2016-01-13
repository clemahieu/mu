#include <gtest/gtest.h>

#include <sstream>

#include <errno.h>

TEST (sscanf, test1)
{
	auto string ("42, is a test");
	char buffer1 [32];
	int val1;
	auto number (sscanf (string, "%d %s", &val1, buffer1));
	ASSERT_EQ (2, number);
	ASSERT_EQ (42, val1);
	ASSERT_EQ (std::string (","), std::string (buffer1));
}

TEST (sscanf, test2)
{
	auto string ("42");
	char buffer1 [32];
	int val1;
	auto number (sscanf (string, "%d %s", &val1, buffer1));
	ASSERT_EQ (1, number);
	ASSERT_EQ (42, val1);
}

TEST (strtoull, test1)
{
	auto string ("42 is a test");
	errno = 0;
	auto value (strtoull (string, nullptr, 0));
	auto newerr (errno);
}