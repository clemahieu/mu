#include <mu/script/iterator.h>

mu::script::iterator::iterator (std::vector <boost::shared_ptr <mu::core::node>> & stack_a, size_t position_a)
	: stack (stack_a),
	position (position_a)
{
}

mu::script::iterator mu::script::iterator::operator ++ ()
{
	++position;
	return *this;
}

mu::script::iterator mu::script::iterator::operator -- ()
{
	--position;
	return *this;
}

bool mu::script::iterator::operator == (mu::script::iterator const & other) const
{
	bool result ((&other.stack == &stack) && (other.position == position));
	return result;
}

bool mu::script::iterator::operator != (mu::script::iterator const & other) const
{
	bool result (!(*this == other));
	return result;
}

mu::script::iterator mu::script::iterator::operator + (size_t offset)
{
	mu::script::iterator result (stack, position + offset);
	return result;
}

mu::script::iterator mu::script::iterator::operator - (size_t offset)
{
	mu::script::iterator result (stack, position - offset);
	return result;
}
			
boost::shared_ptr <mu::core::node> & mu::script::iterator::operator * ()
{
	boost::shared_ptr <mu::core::node> & result (stack [position]);
	return result;
}