#include <mu/script/closure/apply.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/closure/operation.h>
#include <mu/script/closure/hole.h>
#include <mu/script/check.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::script::closure::apply::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 0)
	{
		auto operation (dynamic_cast <mu::script::closure::operation *> (context_a.parameters (0)));
		if (operation != nullptr)
		{			
			std::vector <size_t> open_l;
			for (size_t position (1), end (context_a.parameters_size ()); position != end; ++position)
			{
				auto val (context_a.parameters (position));
				auto hole (dynamic_cast <mu::script::closure::hole *> (val));
				if (hole == nullptr)
				{
					operation->closed [operation->open [position - 1]] = val;
				}
				else
				{
					open_l.push_back (operation->open [position - 1]);
				}
				context_a.push (new (GC) mu::script::closure::operation (operation->operation_m, open_l, operation->closed));
			}
		}
		else
		{
			mu::script::invalid_type (context_a, context_a.parameters (0), typeid (mu::script::closure::operation), 0);
			result = false;
		}
	}
	else
	{
		mu::stringstream message;
		message << name ();
		message << L" must have at least one argument";
		context_a.errors (message.str ());
		result = false;
	}
	return result;
}

mu::string mu::script::closure::apply::name ()
{
	return mu::string (U"mu::script::closure::apply");
}