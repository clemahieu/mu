#include <mu/script_runtime/iterator.h>

mu::script_runtime::iterator::iterator (std::vector <boost::shared_ptr <mu::core::node>> & stack_a, size_t position_a)
	: stack (stack_a),
	position (position_a)
{
}

mu::script_runtime::iterator mu::script_runtime::iterator::operator ++ ()
{
	mu::script_runtime::iterator result (stack, position + 1);
	return result;
}

mu::script_runtime::iterator mu::script_runtime::iterator::operator -- ()
{
	mu::script_runtime::iterator result (stack, position - 1);
	return result;
}

bool mu::script_runtime::iterator::operator == (mu::script_runtime::iterator const & other)
{
	bool result ((other.stack == stack) && (other.position == position));
	return result;
}

bool mu::script_runtime::iterator::operator != (mu::script_runtime::iterator const & other)
{
	bool result (!(*this == other));
	return result;
}

mu::script_runtime::iterator mu::script_runtime::iterator::operator + (size_t offset)
{
	mu::script_runtime::iterator result (stack, position + offset);
	return result;
}

mu::script_runtime::iterator mu::script_runtime::iterator::operator - (size_t offset)
{
	mu::script_runtime::iterator result (stack, position - offset);
	return result;
}
			
boost::shared_ptr <mu::core::node> mu::script_runtime::iterator::operator * ()
{
	auto result (stack [position]);
	return result;
}