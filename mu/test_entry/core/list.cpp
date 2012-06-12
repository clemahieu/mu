#include <gtest/gtest.h>

#include <list>

TEST (core_test, list1)
{
	std::list <size_t> list;
	list.insert (list.end (), 0);
}