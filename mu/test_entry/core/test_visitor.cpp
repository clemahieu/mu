#include <mu/test_entry/core/test_visitor.h>

void mu::core_test::test_visitor::operator () (mu::core::cluster * cluster_a)
{
	clusters.push_back (cluster_a);
}

void mu::core_test::test_visitor::operator () (mu::core::expression * expression_a)
{
	expressions.push_back (expression_a);
}

void mu::core_test::test_visitor::operator() (mu::core::parameters * parameters_a)
{
	parameters.push_back (parameters_a);
}

void mu::core_test::test_visitor::operator () (mu::core::reference * reference_a)
{
	references.push_back (reference_a);
}

void mu::core_test::test_visitor::operator () (mu::core::node * node_a)
{
	nodes.push_back (node_a);
}

void mu::core_test::test_visitor::operator() (mu::core::routine * routine_a)
{
	routines.push_back (routine_a);
}