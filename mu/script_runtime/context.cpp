#include <mu/script_runtime/context.h>

#include <mu/core/errors/null.h>
#include <mu/script_runtime/operation.h>
#include <mu/script_runtime/location.h>

#include <boost/make_shared.hpp>

mu::script_runtime::context::context ()
	: frame_begin (0),
	base_begin (0),
	base_end (0),
	errors (boost::make_shared <mu::core::errors::null> ())
{
	push (boost::make_shared <mu::core::node> ());
	enter ();
}

mu::script_runtime::context::context (mu::core::errors::errors errors_a)
	: frame_begin (0),
	base_begin (0),
	base_end (0),
	errors (errors_a)
{
	push (boost::make_shared <mu::core::node> ());
	enter ();
}

bool mu::script_runtime::context::operator () ()
{
	bool result (true);
	if (working_size () > 0)
	{
		auto operation (boost::dynamic_pointer_cast <mu::script_runtime::operation> (working (0)));
		if (operation.get () != nullptr)
		{
			enter ();
			result = (*operation) (*this);
			leave ();
		}
		else
		{
			result = false;
		}
	}
	else
	{
		result = false;
	}
	drop ();
	return result;
}

boost::shared_ptr <mu::core::node> mu::script_runtime::context::parameters (size_t offset)
{
	assert (offset < parameters_size ());
	auto result (stack [base_begin + offset]);
	assert (result.get () != nullptr);
	return result;
}

size_t mu::script_runtime::context::parameters_size ()
{
	auto result (base_end - base_begin - 2);
	assert (result < 32000);
	return result;
}

boost::shared_ptr <mu::core::node> mu::script_runtime::context::locals (size_t offset)
{
	assert (offset < locals_size ());
	auto result (stack [base_end + offset]);
	assert (result.get () != nullptr);
	return result;
}

size_t mu::script_runtime::context::locals_size ()
{
	auto result (frame_begin - base_end);
	assert (result < 32000);
	return result;
}

boost::shared_ptr <mu::core::node> mu::script_runtime::context::working (size_t offset)
{
	assert (offset < working_size ());
	auto result (stack [frame_begin + offset]);
	assert (result.get () != nullptr);
	return result;
}

size_t mu::script_runtime::context::working_size ()
{
	auto result (stack.size () - frame_begin);
	assert (result < 32000);
	return result;
}

void mu::script_runtime::context::drop ()
{
	assert (frame_begin <= stack.size ());
	stack.resize (frame_begin);
}

void mu::script_runtime::context::push (boost::shared_ptr <mu::core::node> node_a)
{
	stack.push_back (node_a);
}

void mu::script_runtime::context::enter ()
{
	assert (stack.size () - frame_begin > 0);
	push (boost::make_shared <mu::script_runtime::location> (base_begin));
	push (boost::make_shared <mu::script_runtime::location> (base_end));
	base_begin = frame_begin + 1;
	base_end = stack.size ();
	frame_begin = stack.size ();
}

void mu::script_runtime::context::leave ()
{
	assert (boost::dynamic_pointer_cast <mu::script_runtime::location> (stack [base_end - 2]).get () != nullptr);
	assert (boost::dynamic_pointer_cast <mu::script_runtime::location> (stack [base_end - 1]).get () != nullptr);
	push (stack [base_end - 2]);
	push (stack [base_end - 1]);
	base_begin = base_begin - 1;
	base_end = base_begin;
	while (frame_begin != stack.size ())
	{
		stack [base_end] = stack [frame_begin];
		++base_end;
		++frame_begin;
	}
	frame_begin = base_begin;
	stack.resize (base_end);
	assert (boost::dynamic_pointer_cast <mu::script_runtime::location> (stack [stack.size () - 2]).get () != nullptr);
	assert (boost::dynamic_pointer_cast <mu::script_runtime::location> (stack [stack.size () - 1]).get () != nullptr);
	base_begin = boost::static_pointer_cast <mu::script_runtime::location> (stack [stack.size () - 2])->position;
	base_end = boost::static_pointer_cast <mu::script_runtime::location> (stack [stack.size () - 1])->position;
	stack.resize (stack.size () - 2);
}

void mu::script_runtime::context::slide ()
{
	frame_begin = stack.size ();
}

mu::script_runtime::iterator mu::script_runtime::context::parameters_begin ()
{
	mu::script_runtime::iterator result (stack, base_begin);
	return result;
}

mu::script_runtime::iterator mu::script_runtime::context::parameters_end ()
{
	mu::script_runtime::iterator result (stack, base_end - 2);
	return result;
}

mu::script_runtime::iterator mu::script_runtime::context::locals_begin ()
{
	mu::script_runtime::iterator result (stack, base_end);
	return result;
}

mu::script_runtime::iterator mu::script_runtime::context::locals_end ()
{
	mu::script_runtime::iterator result (stack, frame_begin);
	return result;
}

mu::script_runtime::iterator mu::script_runtime::context::working_begin ()
{
	mu::script_runtime::iterator result (stack, frame_begin);
	return result;
}

mu::script_runtime::iterator mu::script_runtime::context::working_end ()
{
	mu::script_runtime::iterator result (stack, stack.size ());
	return result;
}