#include "operation.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/integer/node.h>

#include <sstream>

void mu::script::times::operation::perform (mu::script::context & context_a)
{
	if (context_a.parameters.size () > 1)
	{
		auto one (boost::dynamic_pointer_cast <mu::script::integer::node> (context_a.parameters [0]));
		auto two (boost::dynamic_pointer_cast <mu::script::operation> (context_a.parameters [1]));
		if (one.get () != nullptr)
		{
			if (two.get () != nullptr)
			{
				std::vector <boost::shared_ptr <mu::core::node>> results_l (context_a.parameters.begin () + 2, context_a.parameters.end ());
				for (size_t i (0), j (one->value); i != j; ++i)
				{
					std::vector <boost::shared_ptr <mu::core::node>> arguments;
					arguments.swap (results_l);
					two->perform (mu::script::context (context_a.errors, arguments, results_l));
				}
				context_a.results.insert (context_a.results.end (), results_l.begin (), results_l.end ());
			}
			else
			{
				invalid_type (context_a.errors, context_a.parameters [1], 1);
			}
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [0], 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << name ();
		message << L" must have at least two arguments";
		(*context_a.errors) (message.str ());
	}
}

std::wstring mu::script::times::operation::name ()
{
	return std::wstring (L"mu::script::times::operation");
}