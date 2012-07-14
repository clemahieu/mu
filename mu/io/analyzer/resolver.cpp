#include <mu/io/analyzer/resolver.h>

#include <mu/core/expression.h>

mu::io::analyzer::resolver::resolver (mu::core::expression * unresolved_a, size_t position_a)
	: unresolved (unresolved_a),
	position (position_a)
{
	assert (unresolved_a->dependencies [position_a] == nullptr);
}

void mu::io::analyzer::resolver::operator () (mu::core::node * node_a)
{
	assert (unresolved->dependencies [position] == nullptr);
	unresolved->dependencies [position] = node_a;

}