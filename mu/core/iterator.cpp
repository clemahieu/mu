#include <mu/core/iterator.h>

mu::core::iterator::iterator (std::vector <mu::core::node *, gc_allocator <mu::core::node *>> & stack_a, size_t position_a)
	: stack (stack_a),
	position (position_a)
{
}

mu::core::iterator mu::core::iterator::operator ++ ()
{
	++position;
	return *this;
}

mu::core::iterator mu::core::iterator::operator -- ()
{
	--position;
	return *this;
}

bool mu::core::iterator::operator == (mu::core::iterator const & other) const
{
	bool result ((&other.stack == &stack) && (other.position == position));
	return result;
}

bool mu::core::iterator::operator != (mu::core::iterator const & other) const
{
	bool result (!(*this == other));
	return result;
}

mu::core::iterator mu::core::iterator::operator + (size_t offset)
{
	mu::core::iterator result (stack, position + offset);
	return result;
}

mu::core::iterator mu::core::iterator::operator - (size_t offset)
{
	mu::core::iterator result (stack, position - offset);
	return result;
}
			
mu::core::node * & mu::core::iterator::operator * ()
{
	mu::core::node * & result (stack [position]);
	return result;
}