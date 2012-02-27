#include "expression.h"

#include <mu/script/runtime/context.h>

mu::script::expression::expression (size_t index_a)
	: index (index_a)
{
}

void mu::script::expression::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target)
{
	assert (context.nodes.size () > index);
	std::vector <boost::shared_ptr <mu::core::node>> & source (context.nodes [index]);
	target.insert (target.end (), source.begin (), source.end ());
}