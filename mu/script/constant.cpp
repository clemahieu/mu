#include "constant.h"

mu::script::constant::constant (boost::shared_ptr <mu::core::node> value_a)
	: value (value_a)
{
}

void mu::script::constant::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target)
{
	target.push_back (value);
}