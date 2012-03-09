#include "create_single.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/closure/operation.h>
#include <mu/script/closure/single.h>
#include <mu/script/check.h>

#include <sstream>

void mu::script::closure::create_single::operator () (mu::script::context & context_a)
{
	if (context_a.parameters.size () > 0)
	{
		auto one (boost::dynamic_pointer_cast <mu::script::operation> (context_a.parameters [0]));
		if (one.get () != nullptr)
		{
			std::vector <boost::shared_ptr <mu::core::node>> closed_l (context_a.parameters.begin () + 1, context_a.parameters.end ());
			context_a.results.push_back (boost::shared_ptr <mu::core::node> (new mu::script::closure::single (closed_l, one)));
		}
		else
		{
			mu::script::invalid_type (context_a.errors, typeid (*context_a.parameters [0].get ()), typeid (mu::script::operation), 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Operation: ";
		message << name ();
		message << L" must have at least one argument";
		(*context_a.errors) (message.str ());
	}
}

std::wstring mu::script::closure::create_single::name ()
{
	return std::wstring (L"mu::script::closure::create_single");
}