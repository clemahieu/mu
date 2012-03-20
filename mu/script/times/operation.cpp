#include <mu/script/times/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/integer/node.h>
#include <mu/script/check.h>

#include <sstream>

bool mu::script::times::operation::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 1)
	{
		auto one (boost::dynamic_pointer_cast <mu::script::integer::node> (context_a.parameters (0)));
		auto two (boost::dynamic_pointer_cast <mu::script::operation> (context_a.parameters (1)));
		if (one.get () != nullptr)
		{
			if (two.get () != nullptr)
			{
				context_a.push (context_a.parameters_begin () + 2, context_a.parameters_end ());
				for (size_t i (0), j (one->value); i != j; ++i)
				{
					(*two) (context_a);
				}
			}
			else
			{
				mu::script::invalid_type (context_a, typeid (*context_a.parameters (1).get ()), typeid (mu::script::operation), 1);
				result = false;
			}
		}
		else
		{
			mu::script::invalid_type (context_a, typeid (*context_a.parameters (0).get ()), typeid (mu::script::integer::node), 0);
			result = false;
		}
	}
	else
	{
		std::wstringstream message;
		message << name ();
		message << L" must have at least two arguments";
		context_a.errors (message.str ());
		result = false;
	}
	return result;
}

std::wstring mu::script::times::operation::name ()
{
	return std::wstring (L"mu::script::times::operation");
}