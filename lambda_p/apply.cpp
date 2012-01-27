#include "apply.h"

void lambda_p::apply::merge (lambda_p::segment <boost::shared_ptr <lambda_p::node>> target, lambda_p::segment <boost::shared_ptr <lambda_p::node>> source)
{
	size_t position (0);
	auto i (source.begin ());
	auto j (source.end ());
	while (i != j)
	{
		auto val (*i);
		if (val.get () != nullptr)
		{
			bool assigned (false);
			while (!assigned)
			{
				if (target.size () <= position)
				{
					target.resize (position + 1);
				}
				if (target [position].get () == nullptr)
				{
					target [position] = val;
					++i;
					assigned = true;
				}
				else
				{
					++position;
				}
			}
		}
		else
		{
			++i;
			++position;
		}
	}
}