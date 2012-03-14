#include <mu/io/analyzer/resolver.h>

#include <mu/core/expression.h>
#include <mu/io/debugging/expression.h>

mu::io::analyzer::resolver::resolver (boost::shared_ptr <mu::core::expression> unresolved_a, boost::shared_ptr <mu::io::debugging::expression> unresolved_info_a, size_t position_a)
	: unresolved (unresolved_a),
	position (position_a),
	unresolved_info (unresolved_info_a)
{
	assert (unresolved_a->dependencies [position_a].get () == nullptr);
	assert (unresolved_info_a->dependencies [position_a] == nullptr);
}

void mu::io::analyzer::resolver::operator () (boost::shared_ptr <mu::core::node> node_a, boost::shared_ptr <mu::io::debugging::node> node_info_a)
{
	assert (unresolved->dependencies [position].get () == nullptr);
	assert (unresolved_info->dependencies [position] == nullptr);
	unresolved->dependencies [position] = node_a;
	unresolved_info->dependencies [position] = node_info_a;

}