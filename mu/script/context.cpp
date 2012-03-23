#include <mu/script/context.h>

#include <mu/core/errors/null.h>
#include <mu/script/operation.h>
#include <mu/script/location.h>
#include <mu/core/routine.h>

#include <boost/make_shared.hpp>

mu::script::context::context ()
	: frame_begin (0),
	base_begin (0),
	base_end (0),
	errors (boost::make_shared <mu::core::errors::null> ())
{
	enter ();
}

mu::script::context::context (mu::core::errors::errors errors_a)
	: frame_begin (0),
	base_begin (0),
	base_end (0),
	errors (errors_a)
{
	enter ();
}

bool mu::script::context::operator () ()
{
	bool result (true);
	if (working_size () > 0)
	{
		auto operation (boost::dynamic_pointer_cast <mu::script::operation> (working (0)));
		if (operation.get () != nullptr)
		{
			frame_begin++;
			enter ();
			result = (*operation) (*this);
			base_begin--;
			leave ();
		}
		else
		{
			errors (L"First node in expression is not an operation");
            result = false;
            drop ();
		}
	}
	else
	{
		result = false;
	}
	return result;
}

boost::shared_ptr <mu::core::node> & mu::script::context::parameters (size_t offset)
{
	assert (offset < parameters_size ());
	boost::shared_ptr <mu::core::node> & result (stack [base_begin + offset]);
	return result;
}

size_t mu::script::context::parameters_size ()
{
	auto result (base_end - base_begin - 2);
	assert (result < 64 * 1024);
	return result;
}

boost::shared_ptr <mu::core::node> & mu::script::context::locals (size_t offset)
{
	assert (offset < locals_size ());
	boost::shared_ptr <mu::core::node> & result (stack [base_end + offset]);
	return result;
}

size_t mu::script::context::locals_size ()
{
	auto result (frame_begin - base_end);
	assert (result < 64 * 1024);
	return result;
}

boost::shared_ptr <mu::core::node> & mu::script::context::working (size_t offset)
{
	assert (offset < working_size ());
	boost::shared_ptr <mu::core::node> & result (stack [frame_begin + offset]);
	return result;
}

size_t mu::script::context::working_size ()
{
	auto result (stack.size () - frame_begin);
	assert (result < 64 * 1024);
	return result;
}

void mu::script::context::drop ()
{
	assert (frame_begin <= stack.size ());
	stack.resize (frame_begin);
}

void mu::script::context::push (boost::shared_ptr <mu::core::node> node_a)
{
	assert (stack.size () < 64 * 1024 && "Stack overflow");
	stack.push_back (node_a);
}

void mu::script::context::reserve (size_t count_a)
{
	assert (working_size () == 0);
	stack.resize (stack.size () + count_a);
	frame_begin = stack.size ();
}

void mu::script::context::enter ()
{
	assert (stack.size () - frame_begin >= 0);
	push (boost::make_shared <mu::script::location> (base_begin));
	push (boost::make_shared <mu::script::location> (base_end));
	base_begin = frame_begin;
	base_end = stack.size ();
	frame_begin = stack.size ();
}

void mu::script::context::leave ()
{
	assert (boost::dynamic_pointer_cast <mu::script::location> (stack [base_end - 2]).get () != nullptr);
	assert (boost::dynamic_pointer_cast <mu::script::location> (stack [base_end - 1]).get () != nullptr);
	push (stack [base_end - 2]);
	push (stack [base_end - 1]);
	base_end = base_begin;
	while (frame_begin != stack.size ())
	{
		stack [base_end] = stack [frame_begin];
		++base_end;
		++frame_begin;
	}
	frame_begin = base_begin;
	stack.resize (base_end);
	assert (boost::dynamic_pointer_cast <mu::script::location> (stack [stack.size () - 2]).get () != nullptr);
	assert (boost::dynamic_pointer_cast <mu::script::location> (stack [stack.size () - 1]).get () != nullptr);
	base_begin = boost::static_pointer_cast <mu::script::location> (stack [stack.size () - 2])->position;
	base_end = boost::static_pointer_cast <mu::script::location> (stack [stack.size () - 1])->position;
	stack.resize (stack.size () - 2);
}

void mu::script::context::slide ()
{
	frame_begin = stack.size ();
}

mu::script::iterator mu::script::context::parameters_begin ()
{
	mu::script::iterator result (stack, base_begin);
	return result;
}

mu::script::iterator mu::script::context::parameters_end ()
{
	mu::script::iterator result (stack, base_end - 2);
	return result;
}

mu::script::iterator mu::script::context::locals_begin ()
{
	mu::script::iterator result (stack, base_end);
	return result;
}

mu::script::iterator mu::script::context::locals_end ()
{
	mu::script::iterator result (stack, frame_begin);
	return result;
}

mu::script::iterator mu::script::context::working_begin ()
{
	mu::script::iterator result (stack, frame_begin);
	return result;
}

mu::script::iterator mu::script::context::working_end ()
{
	mu::script::iterator result (stack, stack.size ());
	return result;
}