#include <mu/script/runtime.constant.h>

mu::script::runtime::constant::constant (boost::shared_ptr <mu::core::node> value_a)
	: value (value_a)
{
}

void mu::script::runtime::constant::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::runtime::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target)
{
	target.push_back (value);
}
