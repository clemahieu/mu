#include "gather.h"

#include <lambda_p/core/target.h>
#include <lambda_p/core/connection.h>

lambda_p::core::gather::gather (boost::shared_ptr <lambda_p::core::target> target_a)
	: target (target_a),
	remaining (0)
{
	assert (target_a != nullptr && L"Null target");
}

void lambda_p::core::gather::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> & arguments_a, size_t sequence)
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

boost::shared_ptr <lambda_p::core::connection> lambda_p::core::gather::operator () (boost::shared_ptr <lambda_p::core::gather> self_a)
{
	assert (self_a.get () == this);
	auto remaining_l (remaining);
	boost::shared_ptr <lambda_p::core::connection> result (new lambda_p::core::connection (self_a, remaining_l));
	++remaining_l;
	remaining = remaining_l;
	arguments.resize (remaining_l);
	return result;
}