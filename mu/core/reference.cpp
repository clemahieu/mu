#include <mu/core/reference.h>

#include <mu/core/visitor.h>

mu::core::reference::reference ()
{
}

mu::core::reference::reference (boost::shared_ptr <mu::core::expression> expression_a, size_t index_a)
	: expression (expression_a),
	index (index_a)
{
}

void mu::core::reference::operator () (mu::core::visitor * visitor_a)
{
	(*visitor_a) (this);
}