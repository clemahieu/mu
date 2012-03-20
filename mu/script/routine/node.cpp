#include <mu/script/routine/node.h>

#include <mu/script/check.h>
#include <mu/script/values/operation.h>
#include <mu/script/routine/locals.h>
#include <mu/core/parameters.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>
#include <mu/core/reference.h>

#include <boost/make_shared.hpp>

#include <sstream>

bool mu::script::routine::node::operator () (mu::script::context & context_a)
{	
	bool result (mu::script::check <mu::script::routine::locals, mu::script::values::operation, mu::core::expression> () (context_a));
	if (result)
	{
		auto locals (boost::static_pointer_cast <mu::script::routine::locals> (context_a.parameters (0)));
		auto parameters (boost::static_pointer_cast <mu::script::values::operation> (context_a.parameters (1)));
		auto three (boost::static_pointer_cast <mu::core::expression> (context_a.parameters (2)));
		for (auto i (three->dependencies.begin ()), j (three->dependencies.end ()); i != j; ++i)
		{
			auto expression_l (boost::dynamic_pointer_cast <mu::core::expression> (*i));
			auto reference_l (boost::dynamic_pointer_cast <mu::core::reference> (*i));
			if (reference_l.get () != nullptr)
			{
				expression_l = reference_l->expression;
			}
			if (expression_l.get () != nullptr)
			{
				auto existing (locals->ranges.find (expression_l));
				if (existing == locals->ranges.end ())
				{					
					locals->ranges [expression_l] = boost::tuple <size_t, size_t> (~0, ~0);
					context_a.push (boost::make_shared <mu::script::routine::node> ());
					context_a.push (locals);
					context_a.push (parameters);
					context_a.push (expression_l);
					result = context_a ();
					locals->ranges [expression_l] = boost::tuple <size_t, size_t> (context_a.locals_size (), context_a.locals_size () + context_a.working_size ());
					context_a.slide ();
				}
				else
				{
					if (existing->second.head == ~0)
					{
						context_a.errors (L"Cycle detected");
						result = false;
					}
					if (existing->second.head == ~0 - 1)
					{
						context_a.errors (L"Dependent expression failed");
						result = false;
					}
				}
			}
		}
		if (result)
		{
			for (auto i (three->dependencies.begin ()), j (three->dependencies.end ()); i != j; ++i)
			{
				auto expression_l (boost::dynamic_pointer_cast <mu::core::expression> (*i));
				if (expression_l.get () != nullptr)
				{
					assert (locals->ranges.find (expression_l) != locals->ranges.end ());
					auto range (locals->ranges [expression_l]);
					assert (range.get <0> () != ~0 && range.get <0> () != ~0 - 1 && range.get <1> () != ~0 && range.get <1> () != ~0 - 1);
					context_a.push (context_a.locals_begin () + range.get <0> (), context_a.locals_begin () + range.get <1> ());
				}
				else
				{
					auto reference_l (boost::dynamic_pointer_cast <mu::core::reference> (*i));
					if (reference_l.get () != nullptr)
					{
						assert (locals->ranges.find (reference_l->expression) != locals->ranges.end ());
						auto range (locals->ranges [reference_l->expression]);
						assert (range.get <0> () != ~0 && range.get <0> () != ~0 - 1 && range.get <1> () != ~0 && range.get <1> () != ~0 - 1);
						if (reference_l->index + range.get <0> () < range.get <1> ())
						{
							context_a.push (context_a.locals (reference_l->index + range.get <0> ()));
						}
						else
						{
							std::wstringstream message;
							message << L"Reference index: ";
							message << reference_l->index;
							message << L" but only have: ";
							message << range.get <0> () - range.get <1> ();
							message << L" nodes";
							context_a.errors (message.str ());
							result = false;
						}
					}
					else
					{
						auto parameters_l (boost::dynamic_pointer_cast <mu::core::parameters> (*i));
						if (parameters_l.get () != nullptr)
						{
							context_a.push (parameters);
						}
						else
						{
							context_a.push (*i);
						}
					}
				}
			}
			if (result)
			{
				result = context_a ();
			}
		}
	}
	return result;
}