#include <mu/script/closure/apply.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/closure/operation.h>
#include <mu/script/closure/hole.h>
#include <mu/script/check.h>

#include <sstream>

bool mu::script::closure::apply::operator () (mu::script_runtime::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 0)
	{
		auto operation (boost::dynamic_pointer_cast <mu::script::closure::operation> (context_a.parameters (0)));
		if (operation.get () != nullptr)
		{			
			std::vector <size_t> open_l;
			for (size_t position (1), end (context_a.parameters_size ()); position != end; ++position)
			{
				auto val (context_a.parameters (position));
				auto hole (boost::dynamic_pointer_cast <mu::script::closure::hole> (val));
				if (hole.get () == nullptr)
				{
					operation->closed [operation->open [position - 1]] = val;
				}
				else
				{
					open_l.push_back (operation->open [position - 1]);
				}
				context_a.push (boost::shared_ptr <mu::core::node> (new mu::script::closure::operation (operation->operation_m, open_l, operation->closed)));
			}
		}
		else
		{
			mu::script::invalid_type (context_a, typeid (*context_a.parameters [0].get ()), typeid (mu::script::closure::operation), 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << name ();
		message << L" must have at least one argument";
		context_a.errors (message.str ());
		result = false;
	}
	return result;
}

std::wstring mu::script::closure::apply::name ()
{
	return std::wstring (L"mu::script::closure::apply");
}