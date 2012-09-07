#include <mu/script/context.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/operation.h>
#include <mu/script/location.h>
#include <mu/script/abort_exception.h>

#include <gc_cpp.h>

#include <assert.h>

mu::script::context::context () :
mu::core::context ()
{
    enter ();
}

mu::script::context::context (mu::core::errors::error_target & target_a) :
mu::core::context (target_a)
{
    enter ();
}

bool mu::script::context::operator () ()
{
    bool result (true);
    try
    {
        if (working_size () > 0)
        {
            auto item (working (0));
            auto operation (dynamic_cast <mu::script::operation *> (item));
            if (operation != nullptr)
            {
                frame_begin++;
                enter ();
                result = (*operation) (*this);
                base_begin--;
                leave ();
            }
            else
            {
                errors (U"First node in expression is not an operation");
                result = false;
                drop ();
            }
        }
        else
        {
            result = false;
        }
    }
    catch (mu::script::abort_exception & e)
    {
        result = false;
    }
	return result;
}

void mu::script::context::enter ()
{
	assert (stack.size () - frame_begin >= 0);
	push (new (GC) mu::script::location (base_begin));
	push (new (GC) mu::script::location (base_end));
	base_begin = frame_begin;
	base_end = stack.size ();
	frame_begin = stack.size ();
}

void mu::script::context::leave ()
{
	assert (dynamic_cast <mu::script::location *> (stack [base_end - 2]) != nullptr);
	assert (dynamic_cast <mu::script::location *> (stack [base_end - 1]) != nullptr);
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
	assert (dynamic_cast <mu::script::location *> (stack [stack.size () - 2]) != nullptr);
	assert (dynamic_cast <mu::script::location *> (stack [stack.size () - 1]) != nullptr);
	base_begin = static_cast <mu::script::location *> (stack [stack.size () - 2])->position;
	base_end = static_cast <mu::script::location *> (stack [stack.size () - 1])->position;
	stack.resize (stack.size () - 2);
}