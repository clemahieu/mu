#include <mu/script/runtime/expression.h>

#include <mu/script/runtime/frame.h>

mu::script::runtime::expression::expression (size_t index_a)
	: index (index_a)
{
}

void mu::script::runtime::expression::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::runtime::frame & frame, std::vector <boost::shared_ptr <mu::core::node>> & target)
{
	assert (frame.nodes.size () > index);
	std::vector <boost::shared_ptr <mu::core::node>> & source (frame.nodes [index]);
	target.insert (target.end (), source.begin (), source.end ());
}