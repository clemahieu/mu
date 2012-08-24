#include <mu/core/context.h>

#include <mu/core/errors/null.h>

#include <gc_cpp.h>

#include <assert.h>

mu::core::context::context ()
	: base_begin (0),
	base_end (0),
	frame_begin (0),
	errors (*new (GC) mu::core::errors::null ())
{
}

mu::core::context::context (mu::core::errors::error_target & errors_a)
	: base_begin (0),
	base_end (0),
	frame_begin (0),
	errors (errors_a)
{
}

mu::core::node * & mu::core::context::parameters (size_t offset)
{
	assert (offset < parameters_size ());
	mu::core::node * & result (stack [base_begin + offset]);
	return result;
}

size_t mu::core::context::parameters_size ()
{
	auto result (base_end - base_begin - 2);
	assert (result < 64 * 1024);
	return result;
}

mu::core::node * & mu::core::context::locals (size_t offset)
{
	assert (offset < locals_size ());
	mu::core::node * & result (stack [base_end + offset]);
	return result;
}

size_t mu::core::context::locals_size ()
{
	auto result (frame_begin - base_end);
	assert (result < 64 * 1024);
	return result;
}

mu::core::node * & mu::core::context::working (size_t offset)
{
	assert (offset < working_size ());
	mu::core::node * & result (stack [frame_begin + offset]);
	return result;
}

size_t mu::core::context::working_size ()
{
	auto result (stack.size () - frame_begin);
	assert (result < 64 * 1024);
	return result;
}

void mu::core::context::drop ()
{
	assert (frame_begin <= stack.size ());
	stack.resize (frame_begin);
}

void mu::core::context::push (mu::core::node * node_a)
{
	assert (stack.size () < 64 * 1024 && "Stack overflow");
	stack.push_back (node_a);
}

void mu::core::context::reserve (size_t count_a)
{
	assert (working_size () == 0);
	stack.resize (stack.size () + count_a);
	frame_begin = stack.size ();
}

void mu::core::context::slide ()
{
	frame_begin = stack.size ();
}

mu::core::iterator mu::core::context::parameters_begin ()
{
	mu::core::iterator result (stack, base_begin);
	return result;
}

mu::core::iterator mu::core::context::parameters_end ()
{
	mu::core::iterator result (stack, base_end - 2);
	return result;
}

mu::core::iterator mu::core::context::locals_begin ()
{
	mu::core::iterator result (stack, base_end);
	return result;
}

mu::core::iterator mu::core::context::locals_end ()
{
	mu::core::iterator result (stack, frame_begin);
	return result;
}

mu::core::iterator mu::core::context::working_begin ()
{
	mu::core::iterator result (stack, frame_begin);
	return result;
}

mu::core::iterator mu::core::context::working_end ()
{
	mu::core::iterator result (stack, stack.size ());
	return result;
}