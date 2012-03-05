#include "expression.h"

#include <mu/script/runtime/context.h>

mu::script::runtime::expression::expression (size_t index_a)
	: index (index_a)
{
}

void mu::script::runtime::expression::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::runtime::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target)
{
	assert (context.nodes.size () > index);
	std::vector <boost::shared_ptr <mu::core::node>> & source (context.nodes [index]);
	target.insert (target.end (), source.begin (), source.end ());
}