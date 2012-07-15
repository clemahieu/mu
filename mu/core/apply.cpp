#include <mu/core/apply.h>

void mu::core::apply::merge (std::vector <mu::core::node *, gc_allocator <mu::core::node *>> & target, std::vector <mu::core::node *, gc_allocator <mu::core::node *>> & source)
{
	size_t position (0);
	auto i (source.begin ());
	auto j (source.end ());
	while (i != j)
	{
		auto val (*i);
		if (val != nullptr)
		{
			bool assigned (false);
			while (!assigned)
			{
				if (target.size () <= position)
				{
					target.resize (position + 1);
				}
				if (target [position] == nullptr)
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