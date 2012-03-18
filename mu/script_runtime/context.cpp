#include <mu/script_runtime/context.h>

#include <mu/script_runtime/operation.h>
#include <mu/script_runtime/location.h>

#include <boost/make_shared.hpp>

mu::script_runtime::context::context ()
	: working_begin (0),
	base_begin (0),
	base_end (0)
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
	assert (base_begin + offset < base_end);
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
	assert (offset + base_end < working_begin);
	auto result (stack [base_end + offset]);
	assert (result.get () != nullptr);
	return result;
}

size_t mu::script_runtime::context::locals_size ()
{
	auto result (working_begin - base_end);
	assert (result < 32000);
	return result;
}

boost::shared_ptr <mu::core::node> mu::script_runtime::context::working (size_t offset)
{
	assert (working_begin + offset < stack.size ());
	auto result (stack [working_begin + offset]);
	assert (result.get () != nullptr);
	return result;
}

size_t mu::script_runtime::context::working_size ()
{
	auto result (stack.size () - working_begin);
	assert (result < 32000);
	return result;
}

void mu::script_runtime::context::drop ()
{
	assert (working_begin <= stack.size ());
	stack.resize (working_begin);
}

void mu::script_runtime::context::push (boost::shared_ptr <mu::core::node> node_a)
{
	stack.push_back (node_a);
}

void mu::script_runtime::context::enter ()
{
	assert (stack.size () - working_begin > 0);
	push (boost::make_shared <mu::script_runtime::location> (base_begin));
	push (boost::make_shared <mu::script_runtime::location> (base_end));
	base_begin = working_begin + 1;
	base_end = stack.size ();
	working_begin = stack.size ();
}

void mu::script_runtime::context::leave ()
{
	assert (boost::dynamic_pointer_cast <mu::script_runtime::location> (stack [base_end - 2]).get () != nullptr);
	assert (boost::dynamic_pointer_cast <mu::script_runtime::location> (stack [base_end - 1]).get () != nullptr);
	push (stack [base_end - 2]);
	push (stack [base_end - 1]);
	base_begin = base_begin - 1;
	base_end = base_begin;
	while (working_begin != stack.size ())
	{
		stack [base_end] = stack [working_begin];
		++base_end;
		++working_begin;
	}
	working_begin = base_end - 2;
	assert (boost::dynamic_pointer_cast <mu::script_runtime::location> (stack [working_begin]).get () != nullptr);
	assert (boost::dynamic_pointer_cast <mu::script_runtime::location> (stack [working_begin + 1]).get () != nullptr);
	base_begin = boost::static_pointer_cast <mu::script_runtime::location> (stack [working_begin])->position;
	base_end = boost::static_pointer_cast <mu::script_runtime::location> (stack [working_begin + 1])->position;
	drop ();
}

void mu::script_runtime::context::slide ()
{
	working_begin = stack.size ();
}