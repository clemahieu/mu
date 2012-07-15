#include <mu/core/apply.h>
#include <mu/core/node.h>
#include <mu/core/segment.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>
#include <gc_allocator.h>

TEST (core_test, apply1)
{
	std::vector <mu::core::node *, gc_allocator <mu::core::node *>> target;
	std::vector <mu::core::node *, gc_allocator <mu::core::node *>> source;
	mu::core::apply::merge (target, source);
	EXPECT_EQ (target.size (), 0);
	EXPECT_EQ (source.size (), 0);
}

TEST (core_test, apply2)
{
	std::vector <mu::core::node *, gc_allocator <mu::core::node *>> target;
	target.push_back (new (GC) mu::core::node);
	std::vector <mu::core::node *, gc_allocator <mu::core::node *>> source;
	mu::core::apply::merge (target, source);
	EXPECT_EQ (target.size (), 1);
	EXPECT_EQ (source.size (), 0);
}

TEST (core_test, apply3)
{
	std::vector <mu::core::node *, gc_allocator <mu::core::node *>> target;
	std::vector <mu::core::node *, gc_allocator <mu::core::node *>> source;
	source.push_back (new (GC) mu::core::node);
	mu::core::apply::merge (target, source);
	EXPECT_EQ (target.size (), 1);
	EXPECT_EQ (source.size (), 1);
	EXPECT_EQ (target [0], source [0]);
}

TEST (core_test, apply4)
{
	std::vector <mu::core::node *, gc_allocator <mu::core::node *>> target;
	std::vector <mu::core::node *, gc_allocator <mu::core::node *>> source;
	source.push_back (nullptr);
	source.push_back (new (GC) mu::core::node);
	mu::core::apply::merge (target, source);
	EXPECT_EQ (target.size (), 2);
	EXPECT_EQ (source.size (), 2);
	EXPECT_EQ (target [0], nullptr);
	EXPECT_EQ (target [1], source [1]);
}