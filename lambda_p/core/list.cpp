#include "list.h"

bool lambda_p::core::list::resolved ()
{
	bool result (true);
	for (auto i (contents.begin ()), j (contents.end ()); result && i != j; ++i)
	{
		auto val (*i);
		result = val.get () != nullptr;
		auto current_l (boost::dynamic_pointer_cast <lambda_p::core::list> (*i));
		if (current_l.get () != nullptr)
		{
			result = current_l->resolved ();
		}
	}
	return result;
}