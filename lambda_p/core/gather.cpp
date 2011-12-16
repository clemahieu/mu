#include "gather.h"

#include <lambda_p/core/target.h>

lambda_p::core::gather::gather (boost::shared_ptr <lambda_p::core::target> target_a, size_t size_a)
	: arguments (size_a),
	target (target_a),
	remaining (size_a)
{
	assert (target_a != nullptr && L"Null target");
}

void lambda_p::core::gather::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments_a, size_t sequence)
{
	assert (arguments [sequence].empty ());
	arguments [sequence].insert (arguments [sequence].end (), arguments_a.begin (), arguments_a.end ());
	--remaining;
	if (remaining == 0)
	{
		std::vector <boost::shared_ptr <lambda_p::core::expression>> all_arguments;
		for (auto i (arguments.begin ()), j (arguments.end ()); i != j; ++i)
		{
			for (auto k (i->begin ()), l (i->end ()); k != l; ++k)
			{
				all_arguments.push_back (*k);
			}
		}
		(*target) (all_arguments);
		remaining = arguments.size ();
		arguments.clear ();
		arguments.resize (remaining);
	}
}