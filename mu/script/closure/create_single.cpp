#include <mu/script/closure/create_single.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/closure/operation.h>
#include <mu/script/closure/single.h>
#include <mu/script/check.h>

#include <sstream>

bool mu::script::closure::create_single::operator () (mu::script_runtime::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 0)
	{
		auto one (boost::dynamic_pointer_cast <mu::script_runtime::operation> (context_a.parameters (0)));
		if (one.get () != nullptr)
		{
			std::vector <boost::shared_ptr <mu::core::node>> closed_l (context_a.parameters_begin () + 1, context_a.parameters_end ());
			context_a.push (boost::shared_ptr <mu::core::node> (new mu::script::closure::single (closed_l, one)));
		}
		else
		{
			mu::script::invalid_type (context_a, typeid (*context_a.parameters (0).get ()), typeid (mu::script::operation), 0);
			result = false;
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Operation: ";
		message << name ();
		message << L" must have at least one argument";
		context_a.errors (message.str ());
		result = false;
	}
	return result;
}

std::wstring mu::script::closure::create_single::name ()
{
	return std::wstring (L"mu::script::closure::create_single");
}