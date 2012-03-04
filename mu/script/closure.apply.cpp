#include <mu/script/closure.apply.h>

#include <mu/core/errors.error_target.h>
#include <mu/script/closure.operation.h>
#include <mu/script/closure.hole.h>

#include <sstream>

void mu::script::closure::apply::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	if (parameters.size () > 0)
	{
		auto operation (boost::dynamic_pointer_cast <mu::script::closure::operation> (parameters [0]));
		if (operation.get () != nullptr)
		{			
			std::vector <size_t> open_l;
			for (size_t position (1), end (parameters.size ()); position != end; ++position)
			{
				auto val (parameters [position]);
				auto hole (boost::dynamic_pointer_cast <mu::script::closure::hole> (val));
				if (hole.get () == nullptr)
				{
					operation->closed [operation->open [position - 1]] = val;
				}
				else
				{
					open_l.push_back (operation->open [position - 1]);
				}
				results.push_back (boost::shared_ptr <mu::core::node> (new mu::script::closure::operation (operation->operation_m, open_l, operation->closed)));
			}
		}
		else
		{
			invalid_type (errors_a, parameters [0], 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << name ();
		message << L" must have at least one argument";
		(*errors_a) (message.str ());
	}
}

std::wstring mu::script::closure::apply::name ()
{
	return std::wstring (L"mu::script::closure::apply");
}
