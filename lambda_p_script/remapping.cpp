#include "remapping.h"

#include <set>

void lambda_p_script::remapping::remap (std::map <boost::shared_ptr <lambda_p::node>, boost::shared_ptr <lambda_p::node>> & remap_a)
{
	std::set <boost::shared_ptr <lambda_p::routine>> unmapped;
	for (auto i (generated.begin ()), j (generated.end ()); i != j; ++i)
	{
		auto new_l (remap_a.find (i->second));
		if (new_l == remap_a.end ())
		{
			unmapped.insert (i->first);
		}
		else
		{
			i->second = new_l->second;
		}
	}
	for (auto i (unmapped.begin ()), j (unmapped.end ()); i != j; ++i)
	{
		generated.erase (*i);
	}
}