#include <mu/script/closure/create_single.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/closure/operation.h>
#include <mu/script/closure/single.h>
#include <mu/script/check.h>

#include <sstream>

#include <boost/make_shared.hpp>

bool mu::script::closure::create_single::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 0)
	{
		std::vector <boost::shared_ptr <mu::core::node>> closed_l;
		for (auto i (context_a.parameters_begin () + 1), j (context_a.parameters_end ()); i != j; ++i)
		{
			closed_l.push_back (*i);
		}
		context_a.push (boost::make_shared <mu::script::closure::single> (closed_l, context_a.parameters (0)));
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