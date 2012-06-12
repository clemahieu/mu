#include <mu/core/apply.h>
#include <mu/core/node.h>
#include <mu/core/segment.h>

#include <gtest/gtest.h>

#include <boost/make_shared.hpp>

TEST (core_test, apply1)
{
	std::vector <boost::shared_ptr <mu::core::node>> target;
	std::vector <boost::shared_ptr <mu::core::node>> source;
	mu::core::apply::merge (target, source);
	EXPECT_EQ (target.size (), 0);
	EXPECT_EQ (source.size (), 0);
}

TEST (core_test, apply2)
{
	std::vector <boost::shared_ptr <mu::core::node>> target;
	target.push_back (boost::make_shared <mu::core::node> ());
	std::vector <boost::shared_ptr <mu::core::node>> source;
	mu::core::apply::merge (target, source);
	EXPECT_EQ (target.size (), 1);
	EXPECT_EQ (source.size (), 0);
}

TEST (core_test, apply3)
{
	std::vector <boost::shared_ptr <mu::core::node>> target;
	std::vector <boost::shared_ptr <mu::core::node>> source;
	source.push_back (boost::make_shared <mu::core::node> ());
	mu::core::apply::merge (target, source);
	EXPECT_EQ (target.size (), 1);
	EXPECT_EQ (source.size (), 1);
	EXPECT_EQ (target [0], source [0]);
}

TEST (core_test, apply4)
{
	std::vector <boost::shared_ptr <mu::core::node>> target;
	std::vector <boost::shared_ptr <mu::core::node>> source;
	source.push_back (boost::shared_ptr <mu::core::node> ());
	source.push_back (boost::make_shared <mu::core::node> ());
	mu::core::apply::merge (target, source);
	EXPECT_EQ (target.size (), 2);
	EXPECT_EQ (source.size (), 2);
	EXPECT_EQ (target [0].get (), nullptr);
	EXPECT_EQ (target [1], source [1]);
}